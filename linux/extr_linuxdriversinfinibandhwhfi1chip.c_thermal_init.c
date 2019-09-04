#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_CFG_THERM_POLL_EN ; 
 int /*<<< orphan*/  CR_SBUS ; 
 int /*<<< orphan*/  CR_THERM_INIT ; 
 scalar_t__ ICODE_RTL_SILICON ; 
 int /*<<< orphan*/  RESET_SBUS_RECEIVER ; 
 int /*<<< orphan*/  SBUS_THERMAL ; 
 int SBUS_THERM_MONITOR_MODE ; 
 int /*<<< orphan*/  SBUS_TIMEOUT ; 
 int /*<<< orphan*/  THERM_FAILURE (struct hfi1_devdata*,int,char*) ; 
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int sbus_request_slow (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int thermal_init(struct hfi1_devdata *dd)
{
	int ret = 0;

	if (dd->icode != ICODE_RTL_SILICON ||
	    check_chip_resource(dd, CR_THERM_INIT, NULL))
		return ret;

	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	if (ret) {
		THERM_FAILURE(dd, ret, "Acquire SBus");
		return ret;
	}

	dd_dev_info(dd, "Initializing thermal sensor\n");
	/* Disable polling of thermal readings */
	write_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x0);
	msleep(100);
	/* Thermal Sensor Initialization */
	/*    Step 1: Reset the Thermal SBus Receiver */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				RESET_SBUS_RECEIVER, 0);
	if (ret) {
		THERM_FAILURE(dd, ret, "Bus Reset");
		goto done;
	}
	/*    Step 2: Set Reset bit in Thermal block */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x1);
	if (ret) {
		THERM_FAILURE(dd, ret, "Therm Block Reset");
		goto done;
	}
	/*    Step 3: Write clock divider value (100MHz -> 2MHz) */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x1,
				WRITE_SBUS_RECEIVER, 0x32);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Clock Div");
		goto done;
	}
	/*    Step 4: Select temperature mode */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x3,
				WRITE_SBUS_RECEIVER,
				SBUS_THERM_MONITOR_MODE);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Mode Sel");
		goto done;
	}
	/*    Step 5: De-assert block reset and start conversion */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x2);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Reset Deassert");
		goto done;
	}
	/*    Step 5.1: Wait for first conversion (21.5ms per spec) */
	msleep(22);

	/* Enable polling of thermal readings */
	write_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x1);

	/* Set initialized flag */
	ret = acquire_chip_resource(dd, CR_THERM_INIT, 0);
	if (ret)
		THERM_FAILURE(dd, ret, "Unable to set thermal init flag");

done:
	release_chip_resource(dd, CR_SBUS);
	return ret;
}
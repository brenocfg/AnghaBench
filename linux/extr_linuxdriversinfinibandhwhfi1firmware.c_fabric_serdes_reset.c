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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_devdata {size_t hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_SBUS ; 
 int /*<<< orphan*/  SBUS_TIMEOUT ; 
 int /*<<< orphan*/  SPICO_FABRIC ; 
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/ * fabric_serdes_broadcast ; 
 int /*<<< orphan*/  fw_fabric ; 
 int /*<<< orphan*/  fw_fabric_serdes_load ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  load_fabric_serdes_firmware (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  turn_off_spicos (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void fabric_serdes_reset(struct hfi1_devdata *dd)
{
	int ret;

	if (!fw_fabric_serdes_load)
		return;

	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	if (ret) {
		dd_dev_err(dd,
			   "Cannot acquire SBus resource to reset fabric SerDes - perhaps you should reboot\n");
		return;
	}
	set_sbus_fast_mode(dd);

	if (is_ax(dd)) {
		/* A0 serdes do not work with a re-download */
		u8 ra = fabric_serdes_broadcast[dd->hfi1_id];

		/* place SerDes in reset and disable SPICO */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000011);
		/* wait 100 refclk cycles @ 156.25MHz => 640ns */
		udelay(1);
		/* remove SerDes reset */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000010);
		/* turn SPICO enable on */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000002);
	} else {
		turn_off_spicos(dd, SPICO_FABRIC);
		/*
		 * No need for firmware retry - what to download has already
		 * been decided.
		 * No need to pay attention to the load return - the only
		 * failure is a validation failure, which has already been
		 * checked by the initial download.
		 */
		(void)load_fabric_serdes_firmware(dd, &fw_fabric);
	}

	clear_sbus_fast_mode(dd);
	release_chip_resource(dd, CR_SBUS);
}
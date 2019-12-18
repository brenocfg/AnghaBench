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
struct da9052 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA9052_FAULTLOG_KEYSHUT ; 
 int DA9052_FAULTLOG_NSDSET ; 
 int /*<<< orphan*/  DA9052_FAULTLOG_REG ; 
 int DA9052_FAULTLOG_TEMPOVER ; 
 int DA9052_FAULTLOG_TWDERROR ; 
 int DA9052_FAULTLOG_VDDFAULT ; 
 int DA9052_FAULTLOG_VDDSTART ; 
 int DA9052_FAULTLOG_WAITSET ; 
 int da9052_reg_read (struct da9052*,int /*<<< orphan*/ ) ; 
 int da9052_reg_write (struct da9052*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int da9052_clear_fault_log(struct da9052 *da9052)
{
	int ret = 0;
	int fault_log = 0;

	fault_log = da9052_reg_read(da9052, DA9052_FAULTLOG_REG);
	if (fault_log < 0) {
		dev_err(da9052->dev,
			"Cannot read FAULT_LOG %d\n", fault_log);
		return fault_log;
	}

	if (fault_log) {
		if (fault_log & DA9052_FAULTLOG_TWDERROR)
			dev_dbg(da9052->dev,
				"Fault log entry detected: TWD_ERROR\n");
		if (fault_log & DA9052_FAULTLOG_VDDFAULT)
			dev_dbg(da9052->dev,
				"Fault log entry detected: VDD_FAULT\n");
		if (fault_log & DA9052_FAULTLOG_VDDSTART)
			dev_dbg(da9052->dev,
				"Fault log entry detected: VDD_START\n");
		if (fault_log & DA9052_FAULTLOG_TEMPOVER)
			dev_dbg(da9052->dev,
				"Fault log entry detected: TEMP_OVER\n");
		if (fault_log & DA9052_FAULTLOG_KEYSHUT)
			dev_dbg(da9052->dev,
				"Fault log entry detected: KEY_SHUT\n");
		if (fault_log & DA9052_FAULTLOG_NSDSET)
			dev_dbg(da9052->dev,
				"Fault log entry detected: nSD_SHUT\n");
		if (fault_log & DA9052_FAULTLOG_WAITSET)
			dev_dbg(da9052->dev,
				"Fault log entry detected: WAIT_SHUT\n");

		ret = da9052_reg_write(da9052,
					DA9052_FAULTLOG_REG,
					0xFF);
		if (ret < 0)
			dev_err(da9052->dev,
				"Cannot reset FAULT_LOG values %d\n", ret);
	}

	return ret;
}
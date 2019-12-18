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
 int /*<<< orphan*/  ALT_FW_8051_NAME_ASIC ; 
 int /*<<< orphan*/  ALT_FW_FABRIC_NAME ; 
 int /*<<< orphan*/  ALT_FW_PCIE_NAME ; 
 int /*<<< orphan*/  ALT_FW_SBUS_NAME ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ FW_EMPTY ; 
 scalar_t__ FW_ERR ; 
 scalar_t__ FW_FINAL ; 
 scalar_t__ FW_TRY ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 scalar_t__ ICODE_RTL_SILICON ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  dd_dev_warn (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  dispose_one_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_8051 ; 
 scalar_t__ fw_8051_load ; 
 int /*<<< orphan*/  fw_8051_name ; 
 int /*<<< orphan*/  fw_err ; 
 int /*<<< orphan*/  fw_fabric ; 
 scalar_t__ fw_fabric_serdes_load ; 
 int /*<<< orphan*/  fw_fabric_serdes_name ; 
 int /*<<< orphan*/  fw_pcie ; 
 scalar_t__ fw_pcie_serdes_load ; 
 int /*<<< orphan*/  fw_pcie_serdes_name ; 
 int /*<<< orphan*/  fw_sbus ; 
 scalar_t__ fw_sbus_load ; 
 int /*<<< orphan*/  fw_sbus_name ; 
 scalar_t__ fw_state ; 
 int obtain_one_firmware (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void __obtain_firmware(struct hfi1_devdata *dd)
{
	int err = 0;

	if (fw_state == FW_FINAL)	/* nothing more to obtain */
		return;
	if (fw_state == FW_ERR)		/* already in error */
		return;

	/* fw_state is FW_EMPTY or FW_TRY */
retry:
	if (fw_state == FW_TRY) {
		/*
		 * We tried the original and it failed.  Move to the
		 * alternate.
		 */
		dd_dev_warn(dd, "using alternate firmware names\n");
		/*
		 * Let others run.  Some systems, when missing firmware, does
		 * something that holds for 30 seconds.  If we do that twice
		 * in a row it triggers task blocked warning.
		 */
		cond_resched();
		if (fw_8051_load)
			dispose_one_firmware(&fw_8051);
		if (fw_fabric_serdes_load)
			dispose_one_firmware(&fw_fabric);
		if (fw_sbus_load)
			dispose_one_firmware(&fw_sbus);
		if (fw_pcie_serdes_load)
			dispose_one_firmware(&fw_pcie);
		fw_8051_name = ALT_FW_8051_NAME_ASIC;
		fw_fabric_serdes_name = ALT_FW_FABRIC_NAME;
		fw_sbus_name = ALT_FW_SBUS_NAME;
		fw_pcie_serdes_name = ALT_FW_PCIE_NAME;

		/*
		 * Add a delay before obtaining and loading debug firmware.
		 * Authorization will fail if the delay between firmware
		 * authorization events is shorter than 50us. Add 100us to
		 * make a delay time safe.
		 */
		usleep_range(100, 120);
	}

	if (fw_sbus_load) {
		err = obtain_one_firmware(dd, fw_sbus_name, &fw_sbus);
		if (err)
			goto done;
	}

	if (fw_pcie_serdes_load) {
		err = obtain_one_firmware(dd, fw_pcie_serdes_name, &fw_pcie);
		if (err)
			goto done;
	}

	if (fw_fabric_serdes_load) {
		err = obtain_one_firmware(dd, fw_fabric_serdes_name,
					  &fw_fabric);
		if (err)
			goto done;
	}

	if (fw_8051_load) {
		err = obtain_one_firmware(dd, fw_8051_name, &fw_8051);
		if (err)
			goto done;
	}

done:
	if (err) {
		/* oops, had problems obtaining a firmware */
		if (fw_state == FW_EMPTY && dd->icode == ICODE_RTL_SILICON) {
			/* retry with alternate (RTL only) */
			fw_state = FW_TRY;
			goto retry;
		}
		dd_dev_err(dd, "unable to obtain working firmware\n");
		fw_state = FW_ERR;
		fw_err = -ENOENT;
	} else {
		/* success */
		if (fw_state == FW_EMPTY &&
		    dd->icode != ICODE_FUNCTIONAL_SIMULATOR)
			fw_state = FW_TRY;	/* may retry later */
		else
			fw_state = FW_FINAL;	/* cannot try again */
	}
}
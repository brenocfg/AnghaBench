#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct csio_hw {char chip_ver; scalar_t__ fw_state; int /*<<< orphan*/  sm; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  tp_vers; int /*<<< orphan*/  fwrev; int /*<<< orphan*/  vpd; TYPE_1__* chip_ops; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_set_mem_win ) (struct csio_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CSIO_DEV_STATE_INIT ; 
 int /*<<< orphan*/  CSIO_HWE_FATAL ; 
 int /*<<< orphan*/  CSIO_HWE_INIT ; 
 int /*<<< orphan*/  CSIO_HWF_USING_SOFT_PARAMS ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  MEMWIN_CSIOSTOR ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2_COMP_TIMEOUT ; 
 int /*<<< orphan*/  PL_REV_A ; 
 int csio_config_device_caps (struct csio_hw*) ; 
 int csio_do_hello (struct csio_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int) ; 
 int csio_get_device_params (struct csio_hw*) ; 
 int csio_hw_check_fwconfig (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int csio_hw_check_fwver (struct csio_hw*) ; 
 int csio_hw_dev_ready (struct csio_hw*) ; 
 int csio_hw_flash_fw (struct csio_hw*,int*) ; 
 int csio_hw_get_flash_params (struct csio_hw*) ; 
 int csio_hw_get_fw_version (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_hw_get_tp_version (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int csio_hw_get_vpd_params (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_hw_print_fw_version (struct csio_hw*,char*) ; 
 int csio_hw_use_fwconfig (struct csio_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,...) ; 
 scalar_t__ csio_is_hw_master (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_sge_init (struct csio_hw*) ; 
 int /*<<< orphan*/  n_err_fatal ; 
 scalar_t__ pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct csio_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_hw_configure(struct csio_hw *hw)
{
	int reset = 1;
	int rv;
	u32 param[1];

	rv = csio_hw_dev_ready(hw);
	if (rv != 0) {
		CSIO_INC_STATS(hw, n_err_fatal);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		goto out;
	}

	/* HW version */
	hw->chip_ver = (char)csio_rd_reg32(hw, PL_REV_A);

	/* Needed for FW download */
	rv = csio_hw_get_flash_params(hw);
	if (rv != 0) {
		csio_err(hw, "Failed to get serial flash params rv:%d\n", rv);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		goto out;
	}

	/* Set PCIe completion timeout to 4 seconds */
	if (pci_is_pcie(hw->pdev))
		pcie_capability_clear_and_set_word(hw->pdev, PCI_EXP_DEVCTL2,
				PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0xd);

	hw->chip_ops->chip_set_mem_win(hw, MEMWIN_CSIOSTOR);

	rv = csio_hw_get_fw_version(hw, &hw->fwrev);
	if (rv != 0)
		goto out;

	csio_hw_print_fw_version(hw, "Firmware revision");

	rv = csio_do_hello(hw, &hw->fw_state);
	if (rv != 0) {
		CSIO_INC_STATS(hw, n_err_fatal);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		goto out;
	}

	/* Read vpd */
	rv = csio_hw_get_vpd_params(hw, &hw->vpd);
	if (rv != 0)
		goto out;

	csio_hw_get_fw_version(hw, &hw->fwrev);
	csio_hw_get_tp_version(hw, &hw->tp_vers);
	if (csio_is_hw_master(hw) && hw->fw_state != CSIO_DEV_STATE_INIT) {

			/* Do firmware update */
		spin_unlock_irq(&hw->lock);
		rv = csio_hw_flash_fw(hw, &reset);
		spin_lock_irq(&hw->lock);

		if (rv != 0)
			goto out;

		rv = csio_hw_check_fwver(hw);
		if (rv < 0)
			goto out;

		/* If the firmware doesn't support Configuration Files,
		 * return an error.
		 */
		rv = csio_hw_check_fwconfig(hw, param);
		if (rv != 0) {
			csio_info(hw, "Firmware doesn't support "
				  "Firmware Configuration files\n");
			goto out;
		}

		/* The firmware provides us with a memory buffer where we can
		 * load a Configuration File from the host if we want to
		 * override the Configuration File in flash.
		 */
		rv = csio_hw_use_fwconfig(hw, reset, param);
		if (rv == -ENOENT) {
			csio_info(hw, "Could not initialize "
				  "adapter, error%d\n", rv);
			goto out;
		}
		if (rv != 0) {
			csio_info(hw, "Could not initialize "
				  "adapter, error%d\n", rv);
			goto out;
		}

	} else {
		rv = csio_hw_check_fwver(hw);
		if (rv < 0)
			goto out;

		if (hw->fw_state == CSIO_DEV_STATE_INIT) {

			hw->flags |= CSIO_HWF_USING_SOFT_PARAMS;

			/* device parameters */
			rv = csio_get_device_params(hw);
			if (rv != 0)
				goto out;

			/* Get device capabilities */
			rv = csio_config_device_caps(hw);
			if (rv != 0)
				goto out;

			/* Configure SGE */
			csio_wr_sge_init(hw);

			/* Post event to notify completion of configuration */
			csio_post_event(&hw->sm, CSIO_HWE_INIT);
			goto out;
		}
	} /* if not master */

out:
	return;
}
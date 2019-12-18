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
struct ath10k_pci {int link_ctl; int /*<<< orphan*/  pdev; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_firmware_mode { ____Placeholder_ath10k_firmware_mode } ath10k_firmware_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPMC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_pci_ce_deinit (struct ath10k*) ; 
 int ath10k_pci_chip_reset (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_fw_crashed_clear (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_fw_crashed_dump (struct ath10k*) ; 
 scalar_t__ ath10k_pci_has_fw_crashed (struct ath10k*) ; 
 int ath10k_pci_init_config (struct ath10k*) ; 
 int ath10k_pci_init_pipes (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int ath10k_pci_wake_target_cpu (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath10k_pci_hif_power_up(struct ath10k *ar,
				   enum ath10k_firmware_mode fw_mode)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif power up\n");

	pcie_capability_read_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				  &ar_pci->link_ctl);
	pcie_capability_write_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				   ar_pci->link_ctl & ~PCI_EXP_LNKCTL_ASPMC);

	/*
	 * Bring the target up cleanly.
	 *
	 * The target may be in an undefined state with an AUX-powered Target
	 * and a Host in WoW mode. If the Host crashes, loses power, or is
	 * restarted (without unloading the driver) then the Target is left
	 * (aux) powered and running. On a subsequent driver load, the Target
	 * is in an unexpected state. We try to catch that here in order to
	 * reset the Target and retry the probe.
	 */
	ret = ath10k_pci_chip_reset(ar);
	if (ret) {
		if (ath10k_pci_has_fw_crashed(ar)) {
			ath10k_warn(ar, "firmware crashed during chip reset\n");
			ath10k_pci_fw_crashed_clear(ar);
			ath10k_pci_fw_crashed_dump(ar);
		}

		ath10k_err(ar, "failed to reset chip: %d\n", ret);
		goto err_sleep;
	}

	ret = ath10k_pci_init_pipes(ar);
	if (ret) {
		ath10k_err(ar, "failed to initialize CE: %d\n", ret);
		goto err_sleep;
	}

	ret = ath10k_pci_init_config(ar);
	if (ret) {
		ath10k_err(ar, "failed to setup init config: %d\n", ret);
		goto err_ce;
	}

	ret = ath10k_pci_wake_target_cpu(ar);
	if (ret) {
		ath10k_err(ar, "could not wake up target CPU: %d\n", ret);
		goto err_ce;
	}

	return 0;

err_ce:
	ath10k_pci_ce_deinit(ar);

err_sleep:
	return ret;
}
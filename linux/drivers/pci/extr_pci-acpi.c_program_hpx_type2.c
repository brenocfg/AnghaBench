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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct hpx_type2 {int revision; int pci_exp_devctl_and; int pci_exp_devctl_or; int pci_exp_lnkctl_and; int pci_exp_lnkctl_or; int unc_err_mask_and; int unc_err_mask_or; int unc_err_sever_and; int unc_err_sever_or; int cor_err_mask_and; int cor_err_mask_or; int adv_err_cap_and; int adv_err_cap_or; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_CAP ; 
 int PCI_ERR_CAP_ECRC_CHKC ; 
 int PCI_ERR_CAP_ECRC_CHKE ; 
 int PCI_ERR_CAP_ECRC_GENC ; 
 int PCI_ERR_CAP_ECRC_GENE ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_SEVER ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_PAYLOAD ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_RCB ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 scalar_t__ pcie_cap_has_lnkctl (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pcie_root_rcb_set (struct pci_dev*) ; 

__attribute__((used)) static void program_hpx_type2(struct pci_dev *dev, struct hpx_type2 *hpx)
{
	int pos;
	u32 reg32;

	if (!hpx)
		return;

	if (!pci_is_pcie(dev))
		return;

	if (hpx->revision > 1) {
		pci_warn(dev, "PCIe settings rev %d not supported\n",
			 hpx->revision);
		return;
	}

	/*
	 * Don't allow _HPX to change MPS or MRRS settings.  We manage
	 * those to make sure they're consistent with the rest of the
	 * platform.
	 */
	hpx->pci_exp_devctl_and |= PCI_EXP_DEVCTL_PAYLOAD |
				    PCI_EXP_DEVCTL_READRQ;
	hpx->pci_exp_devctl_or &= ~(PCI_EXP_DEVCTL_PAYLOAD |
				    PCI_EXP_DEVCTL_READRQ);

	/* Initialize Device Control Register */
	pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
			~hpx->pci_exp_devctl_and, hpx->pci_exp_devctl_or);

	/* Initialize Link Control Register */
	if (pcie_cap_has_lnkctl(dev)) {

		/*
		 * If the Root Port supports Read Completion Boundary of
		 * 128, set RCB to 128.  Otherwise, clear it.
		 */
		hpx->pci_exp_lnkctl_and |= PCI_EXP_LNKCTL_RCB;
		hpx->pci_exp_lnkctl_or &= ~PCI_EXP_LNKCTL_RCB;
		if (pcie_root_rcb_set(dev))
			hpx->pci_exp_lnkctl_or |= PCI_EXP_LNKCTL_RCB;

		pcie_capability_clear_and_set_word(dev, PCI_EXP_LNKCTL,
			~hpx->pci_exp_lnkctl_and, hpx->pci_exp_lnkctl_or);
	}

	/* Find Advanced Error Reporting Enhanced Capability */
	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	if (!pos)
		return;

	/* Initialize Uncorrectable Error Mask Register */
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, &reg32);
	reg32 = (reg32 & hpx->unc_err_mask_and) | hpx->unc_err_mask_or;
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, reg32);

	/* Initialize Uncorrectable Error Severity Register */
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &reg32);
	reg32 = (reg32 & hpx->unc_err_sever_and) | hpx->unc_err_sever_or;
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, reg32);

	/* Initialize Correctable Error Mask Register */
	pci_read_config_dword(dev, pos + PCI_ERR_COR_MASK, &reg32);
	reg32 = (reg32 & hpx->cor_err_mask_and) | hpx->cor_err_mask_or;
	pci_write_config_dword(dev, pos + PCI_ERR_COR_MASK, reg32);

	/* Initialize Advanced Error Capabilities and Control Register */
	pci_read_config_dword(dev, pos + PCI_ERR_CAP, &reg32);
	reg32 = (reg32 & hpx->adv_err_cap_and) | hpx->adv_err_cap_or;

	/* Don't enable ECRC generation or checking if unsupported */
	if (!(reg32 & PCI_ERR_CAP_ECRC_GENC))
		reg32 &= ~PCI_ERR_CAP_ECRC_GENE;
	if (!(reg32 & PCI_ERR_CAP_ECRC_CHKC))
		reg32 &= ~PCI_ERR_CAP_ECRC_CHKE;
	pci_write_config_dword(dev, pos + PCI_ERR_CAP, reg32);

	/*
	 * FIXME: The following two registers are not supported yet.
	 *
	 *   o Secondary Uncorrectable Error Severity Register
	 *   o Secondary Uncorrectable Error Mask Register
	 */
}
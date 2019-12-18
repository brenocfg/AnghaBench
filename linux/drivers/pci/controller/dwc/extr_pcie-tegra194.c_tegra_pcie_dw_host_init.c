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
struct tegra_pcie_dw {int /*<<< orphan*/  core_clk; scalar_t__ pcie_cap_base; int /*<<< orphan*/  core_rst; } ;
struct pcie_port {int dummy; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_CTRL ; 
 int APPL_CTRL_LTSSM_EN ; 
 int /*<<< orphan*/  APPL_DEBUG ; 
 int APPL_DEBUG_LTSSM_STATE_MASK ; 
 int APPL_DEBUG_LTSSM_STATE_SHIFT ; 
 int /*<<< orphan*/  APPL_LINK_STATUS ; 
 int APPL_LINK_STATUS_RDLH_LINK_UP ; 
 int PCI_DLF_CAP ; 
 int PCI_DLF_EXCHANGE_ENABLE ; 
 scalar_t__ PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_CLS ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_DLF ; 
 int appl_readl (struct tegra_pcie_dw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int dw_pcie_find_ext_capability (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int dw_pcie_readl_dbi (struct dw_pcie*,int) ; 
 int dw_pcie_readw_dbi (struct dw_pcie*,scalar_t__) ; 
 scalar_t__ dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int,int) ; 
 int /*<<< orphan*/ * pcie_gen_freq ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcie_enable_interrupts (struct pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_prepare_host (struct pcie_port*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct tegra_pcie_dw* to_tegra_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int tegra_pcie_dw_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val, tmp, offset, speed;

	tegra_pcie_prepare_host(pp);

	if (dw_pcie_wait_for_link(pci)) {
		/*
		 * There are some endpoints which can't get the link up if
		 * root port has Data Link Feature (DLF) enabled.
		 * Refer Spec rev 4.0 ver 1.0 sec 3.4.2 & 7.7.4 for more info
		 * on Scaled Flow Control and DLF.
		 * So, need to confirm that is indeed the case here and attempt
		 * link up once again with DLF disabled.
		 */
		val = appl_readl(pcie, APPL_DEBUG);
		val &= APPL_DEBUG_LTSSM_STATE_MASK;
		val >>= APPL_DEBUG_LTSSM_STATE_SHIFT;
		tmp = appl_readl(pcie, APPL_LINK_STATUS);
		tmp &= APPL_LINK_STATUS_RDLH_LINK_UP;
		if (!(val == 0x11 && !tmp)) {
			/* Link is down for all good reasons */
			return 0;
		}

		dev_info(pci->dev, "Link is down in DLL");
		dev_info(pci->dev, "Trying again with DLFE disabled\n");
		/* Disable LTSSM */
		val = appl_readl(pcie, APPL_CTRL);
		val &= ~APPL_CTRL_LTSSM_EN;
		appl_writel(pcie, val, APPL_CTRL);

		reset_control_assert(pcie->core_rst);
		reset_control_deassert(pcie->core_rst);

		offset = dw_pcie_find_ext_capability(pci, PCI_EXT_CAP_ID_DLF);
		val = dw_pcie_readl_dbi(pci, offset + PCI_DLF_CAP);
		val &= ~PCI_DLF_EXCHANGE_ENABLE;
		dw_pcie_writel_dbi(pci, offset, val);

		tegra_pcie_prepare_host(pp);

		if (dw_pcie_wait_for_link(pci))
			return 0;
	}

	speed = dw_pcie_readw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKSTA) &
		PCI_EXP_LNKSTA_CLS;
	clk_set_rate(pcie->core_clk, pcie_gen_freq[speed - 1]);

	tegra_pcie_enable_interrupts(pp);

	return 0;
}
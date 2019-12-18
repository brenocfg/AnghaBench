#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_pcie_dw {int /*<<< orphan*/  pex_ctl_supply; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  core_apb_rst; int /*<<< orphan*/  supports_clkreq; int /*<<< orphan*/  pci; int /*<<< orphan*/  pcie_cap_base; int /*<<< orphan*/  core_rst; TYPE_2__* atu_dma_res; TYPE_1__* dbi_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int start; } ;
struct TYPE_3__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_CFG_BASE_ADDR ; 
 int APPL_CFG_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  APPL_CFG_IATU_DMA_BASE_ADDR ; 
 int APPL_CFG_IATU_DMA_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  APPL_CFG_MISC ; 
 int APPL_CFG_MISC_ARCACHE_SHIFT ; 
 int APPL_CFG_MISC_ARCACHE_VAL ; 
 int /*<<< orphan*/  APPL_CFG_SLCG_OVERRIDE ; 
 int /*<<< orphan*/  APPL_CTRL ; 
 int APPL_CTRL_HW_HOT_RST_EN ; 
 int APPL_CTRL_HW_HOT_RST_MODE_MASK ; 
 int APPL_CTRL_HW_HOT_RST_MODE_SHIFT ; 
 int APPL_CTRL_SYS_PRE_DET_STATE ; 
 int /*<<< orphan*/  APPL_DM_TYPE ; 
 int APPL_DM_TYPE_RP ; 
 int /*<<< orphan*/  APPL_PINMUX ; 
 int APPL_PINMUX_CLKREQ_OUT_OVRD ; 
 int APPL_PINMUX_CLKREQ_OUT_OVRD_EN ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int appl_readl (struct tegra_pcie_dw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  disable_aspm_l11 (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  disable_aspm_l12 (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  dw_pcie_find_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int tegra_pcie_bpmp_set_ctrl_state (struct tegra_pcie_dw*,int) ; 
 int /*<<< orphan*/  tegra_pcie_disable_slot_regulators (struct tegra_pcie_dw*) ; 
 int tegra_pcie_enable_phy (struct tegra_pcie_dw*) ; 
 int tegra_pcie_enable_slot_regulators (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int tegra_pcie_config_controller(struct tegra_pcie_dw *pcie,
					bool en_hw_hot_rst)
{
	int ret;
	u32 val;

	ret = tegra_pcie_bpmp_set_ctrl_state(pcie, true);
	if (ret) {
		dev_err(pcie->dev,
			"Failed to enable controller %u: %d\n", pcie->cid, ret);
		return ret;
	}

	ret = tegra_pcie_enable_slot_regulators(pcie);
	if (ret < 0)
		goto fail_slot_reg_en;

	ret = regulator_enable(pcie->pex_ctl_supply);
	if (ret < 0) {
		dev_err(pcie->dev, "Failed to enable regulator: %d\n", ret);
		goto fail_reg_en;
	}

	ret = clk_prepare_enable(pcie->core_clk);
	if (ret) {
		dev_err(pcie->dev, "Failed to enable core clock: %d\n", ret);
		goto fail_core_clk;
	}

	ret = reset_control_deassert(pcie->core_apb_rst);
	if (ret) {
		dev_err(pcie->dev, "Failed to deassert core APB reset: %d\n",
			ret);
		goto fail_core_apb_rst;
	}

	if (en_hw_hot_rst) {
		/* Enable HW_HOT_RST mode */
		val = appl_readl(pcie, APPL_CTRL);
		val &= ~(APPL_CTRL_HW_HOT_RST_MODE_MASK <<
			 APPL_CTRL_HW_HOT_RST_MODE_SHIFT);
		val |= APPL_CTRL_HW_HOT_RST_EN;
		appl_writel(pcie, val, APPL_CTRL);
	}

	ret = tegra_pcie_enable_phy(pcie);
	if (ret) {
		dev_err(pcie->dev, "Failed to enable PHY: %d\n", ret);
		goto fail_phy;
	}

	/* Update CFG base address */
	appl_writel(pcie, pcie->dbi_res->start & APPL_CFG_BASE_ADDR_MASK,
		    APPL_CFG_BASE_ADDR);

	/* Configure this core for RP mode operation */
	appl_writel(pcie, APPL_DM_TYPE_RP, APPL_DM_TYPE);

	appl_writel(pcie, 0x0, APPL_CFG_SLCG_OVERRIDE);

	val = appl_readl(pcie, APPL_CTRL);
	appl_writel(pcie, val | APPL_CTRL_SYS_PRE_DET_STATE, APPL_CTRL);

	val = appl_readl(pcie, APPL_CFG_MISC);
	val |= (APPL_CFG_MISC_ARCACHE_VAL << APPL_CFG_MISC_ARCACHE_SHIFT);
	appl_writel(pcie, val, APPL_CFG_MISC);

	if (!pcie->supports_clkreq) {
		val = appl_readl(pcie, APPL_PINMUX);
		val |= APPL_PINMUX_CLKREQ_OUT_OVRD_EN;
		val |= APPL_PINMUX_CLKREQ_OUT_OVRD;
		appl_writel(pcie, val, APPL_PINMUX);
	}

	/* Update iATU_DMA base address */
	appl_writel(pcie,
		    pcie->atu_dma_res->start & APPL_CFG_IATU_DMA_BASE_ADDR_MASK,
		    APPL_CFG_IATU_DMA_BASE_ADDR);

	reset_control_deassert(pcie->core_rst);

	pcie->pcie_cap_base = dw_pcie_find_capability(&pcie->pci,
						      PCI_CAP_ID_EXP);

	/* Disable ASPM-L1SS advertisement as there is no CLKREQ routing */
	if (!pcie->supports_clkreq) {
		disable_aspm_l11(pcie);
		disable_aspm_l12(pcie);
	}

	return ret;

fail_phy:
	reset_control_assert(pcie->core_apb_rst);
fail_core_apb_rst:
	clk_disable_unprepare(pcie->core_clk);
fail_core_clk:
	regulator_disable(pcie->pex_ctl_supply);
fail_reg_en:
	tegra_pcie_disable_slot_regulators(pcie);
fail_slot_reg_en:
	tegra_pcie_bpmp_set_ctrl_state(pcie, false);

	return ret;
}
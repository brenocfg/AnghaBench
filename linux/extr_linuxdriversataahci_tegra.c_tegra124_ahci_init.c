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
typedef  size_t u32 ;
struct tegra_ahci_priv {scalar_t__ sata_regs; } ;
struct sata_pad_calibration {size_t gen1_tx_amp; size_t gen1_tx_peak; size_t gen2_tx_amp; size_t gen2_tx_peak; } ;
struct ahci_host_priv {struct tegra_ahci_priv* plat_data; } ;

/* Variables and functions */
 size_t BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_SATA_CALIB ; 
 size_t FUSE_SATA_CALIB_MASK ; 
 scalar_t__ SCFG_OFFSET ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL11 ; 
 size_t T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL1_GEN1 ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL1_GEN2 ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK ; 
 size_t T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL2 ; 
 size_t T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1 ; 
 scalar_t__ T_SATA0_INDEX ; 
 size_t readl (scalar_t__) ; 
 struct sata_pad_calibration* tegra124_pad_calibration ; 
 int tegra_fuse_readl (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int tegra124_ahci_init(struct ahci_host_priv *hpriv)
{
	struct tegra_ahci_priv *tegra = hpriv->plat_data;
	struct sata_pad_calibration calib;
	int ret;
	u32 val;

	/* Pad calibration */
	ret = tegra_fuse_readl(FUSE_SATA_CALIB, &val);
	if (ret)
		return ret;

	calib = tegra124_pad_calibration[val & FUSE_SATA_CALIB_MASK];

	writel(BIT(0), tegra->sata_regs + SCFG_OFFSET + T_SATA0_INDEX);

	val = readl(tegra->sata_regs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN1);
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK;
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK;
	val |= calib.gen1_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT;
	val |= calib.gen1_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT;
	writel(val, tegra->sata_regs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTRL1_GEN1);

	val = readl(tegra->sata_regs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN2);
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK;
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK;
	val |= calib.gen2_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT;
	val |= calib.gen2_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT;
	writel(val, tegra->sata_regs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTRL1_GEN2);

	writel(T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ,
	       tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL11);
	writel(T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1,
	       tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL2);

	writel(0, tegra->sata_regs + SCFG_OFFSET + T_SATA0_INDEX);

	return 0;
}
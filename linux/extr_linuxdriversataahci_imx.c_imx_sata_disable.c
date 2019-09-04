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
struct imx_ahci_priv {int type; int /*<<< orphan*/  sata_ref_clk; int /*<<< orphan*/  epcs_tx_clk; int /*<<< orphan*/  epcs_rx_clk; int /*<<< orphan*/  gpr; scalar_t__ no_device; } ;
struct ahci_host_priv {struct imx_ahci_priv* plat_data; } ;

/* Variables and functions */
#define  AHCI_IMX6Q 130 
#define  AHCI_IMX6QP 129 
#define  AHCI_IMX8QM 128 
 int IMX6Q_GPR13_SATA_MPLL_CLK_EN ; 
 int IMX6Q_GPR5_SATA_SW_PD ; 
 int /*<<< orphan*/  IOMUXC_GPR13 ; 
 int /*<<< orphan*/  IOMUXC_GPR5 ; 
 int /*<<< orphan*/  ahci_platform_disable_regulators (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void imx_sata_disable(struct ahci_host_priv *hpriv)
{
	struct imx_ahci_priv *imxpriv = hpriv->plat_data;

	if (imxpriv->no_device)
		return;

	switch (imxpriv->type) {
	case AHCI_IMX6QP:
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR5,
				   IMX6Q_GPR5_SATA_SW_PD,
				   IMX6Q_GPR5_SATA_SW_PD);
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN,
				   !IMX6Q_GPR13_SATA_MPLL_CLK_EN);
		break;

	case AHCI_IMX6Q:
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN,
				   !IMX6Q_GPR13_SATA_MPLL_CLK_EN);
		break;

	case AHCI_IMX8QM:
		clk_disable_unprepare(imxpriv->epcs_rx_clk);
		clk_disable_unprepare(imxpriv->epcs_tx_clk);
		break;

	default:
		break;
	}

	clk_disable_unprepare(imxpriv->sata_ref_clk);

	ahci_platform_disable_regulators(hpriv);
}
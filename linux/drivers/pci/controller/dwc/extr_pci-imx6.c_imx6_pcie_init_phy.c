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
struct imx6_pcie {int tx_deemph_gen1; int tx_deemph_gen2_3p5db; int tx_deemph_gen2_6db; int tx_swing_full; int tx_swing_low; int /*<<< orphan*/  iomuxc_gpr; TYPE_1__* drvdata; } ;
struct TYPE_2__ {int variant; } ;

/* Variables and functions */
 int IMX6Q_GPR12_LOS_LEVEL ; 
 int IMX6Q_GPR12_PCIE_CTL_2 ; 
 int IMX6Q_GPR8_TX_DEEMPH_GEN1 ; 
 int IMX6Q_GPR8_TX_DEEMPH_GEN2_3P5DB ; 
 int IMX6Q_GPR8_TX_DEEMPH_GEN2_6DB ; 
 int IMX6Q_GPR8_TX_SWING_FULL ; 
 int IMX6Q_GPR8_TX_SWING_LOW ; 
#define  IMX6SX 130 
 int IMX6SX_GPR12_PCIE_RX_EQ_2 ; 
 int IMX6SX_GPR12_PCIE_RX_EQ_MASK ; 
#define  IMX7D 129 
 int IMX7D_GPR12_PCIE_PHY_REFCLK_SEL ; 
#define  IMX8MQ 128 
 int IMX8MQ_GPR_PCIE_REF_USE_PAD ; 
 int /*<<< orphan*/  IOMUXC_GPR12 ; 
 int /*<<< orphan*/  IOMUXC_GPR8 ; 
 int /*<<< orphan*/  imx6_pcie_configure_type (struct imx6_pcie*) ; 
 int /*<<< orphan*/  imx6_pcie_grp_offset (struct imx6_pcie*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void imx6_pcie_init_phy(struct imx6_pcie *imx6_pcie)
{
	switch (imx6_pcie->drvdata->variant) {
	case IMX8MQ:
		/*
		 * TODO: Currently this code assumes external
		 * oscillator is being used
		 */
		regmap_update_bits(imx6_pcie->iomuxc_gpr,
				   imx6_pcie_grp_offset(imx6_pcie),
				   IMX8MQ_GPR_PCIE_REF_USE_PAD,
				   IMX8MQ_GPR_PCIE_REF_USE_PAD);
		break;
	case IMX7D:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX7D_GPR12_PCIE_PHY_REFCLK_SEL, 0);
		break;
	case IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_RX_EQ_MASK,
				   IMX6SX_GPR12_PCIE_RX_EQ_2);
		/* FALLTHROUGH */
	default:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2, 0 << 10);

		/* configure constant input signal to the pcie ctrl and phy */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_LOS_LEVEL, 9 << 4);

		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN1,
				   imx6_pcie->tx_deemph_gen1 << 0);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_3P5DB,
				   imx6_pcie->tx_deemph_gen2_3p5db << 6);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_6DB,
				   imx6_pcie->tx_deemph_gen2_6db << 12);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_FULL,
				   imx6_pcie->tx_swing_full << 18);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_LOW,
				   imx6_pcie->tx_swing_low << 25);
		break;
	}

	imx6_pcie_configure_type(imx6_pcie);
}
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
struct mt7621_pci_phy_instance {int index; } ;
struct mt7621_pci_phy {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RG_P0_TO_P1_WIDTH ; 
 int RG_PE1_FRC_H_XTAL_REG ; 
 int RG_PE1_FRC_H_XTAL_TYPE ; 
 int RG_PE1_FRC_MSTCKDIV ; 
 int RG_PE1_FRC_PHY_EN ; 
 int RG_PE1_FRC_PHY_REG ; 
 int RG_PE1_H_LCDDS_SSC_DELTA ; 
 int RG_PE1_H_LCDDS_SSC_DELTA1 ; 
 int RG_PE1_H_LCDDS_SSC_DELTA1_VAL (int) ; 
 int RG_PE1_H_LCDDS_SSC_DELTA_REG ; 
 int RG_PE1_H_LCDDS_SSC_DELTA_VAL (int) ; 
 int RG_PE1_H_LCDDS_SSC_PRD ; 
 int RG_PE1_H_LCDDS_SSC_PRD_REG ; 
 int RG_PE1_H_LCDDS_SSC_PRD_VAL (int) ; 
 int RG_PE1_H_PLL_BC ; 
 int RG_PE1_H_PLL_BC_VAL (int) ; 
 int RG_PE1_H_PLL_BP ; 
 int RG_PE1_H_PLL_BP_VAL (int) ; 
 int RG_PE1_H_PLL_BR ; 
 int RG_PE1_H_PLL_BR_REG ; 
 int RG_PE1_H_PLL_BR_VAL (int) ; 
 int RG_PE1_H_PLL_FBKSEL ; 
 int RG_PE1_H_PLL_FBKSEL_REG ; 
 int RG_PE1_H_PLL_FBKSEL_VAL (int) ; 
 int RG_PE1_H_PLL_IC ; 
 int RG_PE1_H_PLL_IC_VAL (int) ; 
 int RG_PE1_H_PLL_IR ; 
 int RG_PE1_H_PLL_IR_VAL (int) ; 
 int RG_PE1_H_PLL_PREDIV ; 
 int RG_PE1_H_PLL_PREDIV_VAL (int) ; 
 int RG_PE1_H_PLL_REG ; 
 int RG_PE1_H_XTAL_TYPE ; 
 int RG_PE1_H_XTAL_TYPE_VAL (int) ; 
 int RG_PE1_LCDDS_CLK_PH_INV ; 
 int RG_PE1_LCDDS_CLK_PH_INV_REG ; 
 int RG_PE1_MSTCKDIV ; 
 int RG_PE1_MSTCKDIV_REG ; 
 int RG_PE1_MSTCKDIV_VAL (int) ; 
 int RG_PE1_PHY_EN ; 
 int RG_PE1_PLL_DIVEN ; 
 int RG_PE1_PLL_DIVEN_VAL (int) ; 
 int /*<<< orphan*/  SYSC_REG_SYSTEM_CONFIG0 ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int phy_read (struct mt7621_pci_phy*,int) ; 
 int /*<<< orphan*/  phy_write (struct mt7621_pci_phy*,int,int) ; 
 int rt_sysc_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7621_set_phy_for_ssc(struct mt7621_pci_phy *phy,
				   struct mt7621_pci_phy_instance *instance)
{
	struct device *dev = phy->dev;
	u32 reg = rt_sysc_r32(SYSC_REG_SYSTEM_CONFIG0);
	u32 offset;
	u32 val;

	reg = (reg >> 6) & 0x7;
	/* Set PCIe Port PHY to disable SSC */
	/* Debug Xtal Type */
	val = phy_read(phy, RG_PE1_FRC_H_XTAL_REG);
	val &= ~(RG_PE1_FRC_H_XTAL_TYPE | RG_PE1_H_XTAL_TYPE);
	val |= RG_PE1_FRC_H_XTAL_TYPE;
	val |= RG_PE1_H_XTAL_TYPE_VAL(0x00);
	phy_write(phy, val, RG_PE1_FRC_H_XTAL_REG);

	/* disable port */
	offset = (instance->index != 1) ?
		RG_PE1_FRC_PHY_REG : RG_PE1_FRC_PHY_REG + RG_P0_TO_P1_WIDTH;
	val = phy_read(phy, offset);
	val &= ~(RG_PE1_FRC_PHY_EN | RG_PE1_PHY_EN);
	val |= RG_PE1_FRC_PHY_EN;
	phy_write(phy, val, offset);

	/* Set Pre-divider ratio (for host mode) */
	val = phy_read(phy, RG_PE1_H_PLL_REG);
	val &= ~(RG_PE1_H_PLL_PREDIV);

	if (reg <= 5 && reg >= 3) { /* 40MHz Xtal */
		val |= RG_PE1_H_PLL_PREDIV_VAL(0x01);
		phy_write(phy, val, RG_PE1_H_PLL_REG);
		dev_info(dev, "Xtal is 40MHz\n");
	} else { /* 25MHz | 20MHz Xtal */
		val |= RG_PE1_H_PLL_PREDIV_VAL(0x00);
		phy_write(phy, val, RG_PE1_H_PLL_REG);
		if (reg >= 6) {
			dev_info(dev, "Xtal is 25MHz\n");

			/* Select feedback clock */
			val = phy_read(phy, RG_PE1_H_PLL_FBKSEL_REG);
			val &= ~(RG_PE1_H_PLL_FBKSEL);
			val |= RG_PE1_H_PLL_FBKSEL_VAL(0x01);
			phy_write(phy, val, RG_PE1_H_PLL_FBKSEL_REG);

			/* DDS NCPO PCW (for host mode) */
			val = phy_read(phy, RG_PE1_H_LCDDS_SSC_PRD_REG);
			val &= ~(RG_PE1_H_LCDDS_SSC_PRD);
			val |= RG_PE1_H_LCDDS_SSC_PRD_VAL(0x18000000);
			phy_write(phy, val, RG_PE1_H_LCDDS_SSC_PRD_REG);

			/* DDS SSC dither period control */
			val = phy_read(phy, RG_PE1_H_LCDDS_SSC_PRD_REG);
			val &= ~(RG_PE1_H_LCDDS_SSC_PRD);
			val |= RG_PE1_H_LCDDS_SSC_PRD_VAL(0x18d);
			phy_write(phy, val, RG_PE1_H_LCDDS_SSC_PRD_REG);

			/* DDS SSC dither amplitude control */
			val = phy_read(phy, RG_PE1_H_LCDDS_SSC_DELTA_REG);
			val &= ~(RG_PE1_H_LCDDS_SSC_DELTA |
				 RG_PE1_H_LCDDS_SSC_DELTA1);
			val |= RG_PE1_H_LCDDS_SSC_DELTA_VAL(0x4a);
			val |= RG_PE1_H_LCDDS_SSC_DELTA1_VAL(0x4a);
			phy_write(phy, val, RG_PE1_H_LCDDS_SSC_DELTA_REG);
		} else {
			dev_info(dev, "Xtal is 20MHz\n");
		}
	}

	/* DDS clock inversion */
	val = phy_read(phy, RG_PE1_LCDDS_CLK_PH_INV_REG);
	val &= ~(RG_PE1_LCDDS_CLK_PH_INV);
	val |= RG_PE1_LCDDS_CLK_PH_INV;
	phy_write(phy, val, RG_PE1_LCDDS_CLK_PH_INV_REG);

	/* Set PLL bits */
	val = phy_read(phy, RG_PE1_H_PLL_REG);
	val &= ~(RG_PE1_H_PLL_BC | RG_PE1_H_PLL_BP | RG_PE1_H_PLL_IR |
		 RG_PE1_H_PLL_IC | RG_PE1_PLL_DIVEN);
	val |= RG_PE1_H_PLL_BC_VAL(0x02);
	val |= RG_PE1_H_PLL_BP_VAL(0x06);
	val |= RG_PE1_H_PLL_IR_VAL(0x02);
	val |= RG_PE1_H_PLL_IC_VAL(0x01);
	val |= RG_PE1_PLL_DIVEN_VAL(0x02);
	phy_write(phy, val, RG_PE1_H_PLL_REG);

	val = phy_read(phy, RG_PE1_H_PLL_BR_REG);
	val &= ~(RG_PE1_H_PLL_BR);
	val |= RG_PE1_H_PLL_BR_VAL(0x00);
	phy_write(phy, val, RG_PE1_H_PLL_BR_REG);

	if (reg <= 5 && reg >= 3) { /* 40MHz Xtal */
		/* set force mode enable of da_pe1_mstckdiv */
		val = phy_read(phy, RG_PE1_MSTCKDIV_REG);
		val &= ~(RG_PE1_MSTCKDIV | RG_PE1_FRC_MSTCKDIV);
		val |= (RG_PE1_MSTCKDIV_VAL(0x01) | RG_PE1_FRC_MSTCKDIV);
		phy_write(phy, val, RG_PE1_MSTCKDIV_REG);
	}
}
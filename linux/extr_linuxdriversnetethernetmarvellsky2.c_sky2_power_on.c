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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_POWER_CTRL ; 
 int /*<<< orphan*/  B2_GP_IO ; 
 int /*<<< orphan*/  B2_Y2_CLK_CTRL ; 
 int /*<<< orphan*/  B2_Y2_CLK_GATE ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 scalar_t__ CHIP_REV_YU_XL_A1 ; 
 int /*<<< orphan*/  GLB_GPIO_STAT_RACE_DIS ; 
 int /*<<< orphan*/  PCI_CFG_REG_1 ; 
 int /*<<< orphan*/  PCI_DEV_REG3 ; 
 int /*<<< orphan*/  PCI_DEV_REG4 ; 
 int /*<<< orphan*/  PCI_DEV_REG5 ; 
 int PC_VAUX_ENA ; 
 int PC_VAUX_OFF ; 
 int PC_VCC_ENA ; 
 int PC_VCC_ON ; 
 int /*<<< orphan*/  P_ASPM_CONTROL_MSK ; 
 int /*<<< orphan*/  P_CTL_TIM_VMAIN_AV_MSK ; 
 int SKY2_HW_ADV_POWER_CTL ; 
 int /*<<< orphan*/  Y2_CLK_DIV_DIS ; 
 int Y2_CLK_GAT_LNK1_DIS ; 
 int Y2_CLK_GAT_LNK2_DIS ; 
 int Y2_COR_CLK_LNK1_DIS ; 
 int Y2_COR_CLK_LNK2_DIS ; 
 int /*<<< orphan*/  Y2_HW_WOL_ON ; 
 int /*<<< orphan*/  Y2_LED_STAT_ON ; 
 int Y2_PCI_CLK_LNK1_DIS ; 
 int Y2_PCI_CLK_LNK2_DIS ; 
 int /*<<< orphan*/  sky2_pci_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sky2_power_on(struct sky2_hw *hw)
{
	/* switch power to VCC (WA for VAUX problem) */
	sky2_write8(hw, B0_POWER_CTRL,
		    PC_VAUX_ENA | PC_VCC_ENA | PC_VAUX_OFF | PC_VCC_ON);

	/* disable Core Clock Division, */
	sky2_write32(hw, B2_Y2_CLK_CTRL, Y2_CLK_DIV_DIS);

	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > CHIP_REV_YU_XL_A1)
		/* enable bits are inverted */
		sky2_write8(hw, B2_Y2_CLK_GATE,
			    Y2_PCI_CLK_LNK1_DIS | Y2_COR_CLK_LNK1_DIS |
			    Y2_CLK_GAT_LNK1_DIS | Y2_PCI_CLK_LNK2_DIS |
			    Y2_COR_CLK_LNK2_DIS | Y2_CLK_GAT_LNK2_DIS);
	else
		sky2_write8(hw, B2_Y2_CLK_GATE, 0);

	if (hw->flags & SKY2_HW_ADV_POWER_CTL) {
		u32 reg;

		sky2_pci_write32(hw, PCI_DEV_REG3, 0);

		reg = sky2_pci_read32(hw, PCI_DEV_REG4);
		/* set all bits to 0 except bits 15..12 and 8 */
		reg &= P_ASPM_CONTROL_MSK;
		sky2_pci_write32(hw, PCI_DEV_REG4, reg);

		reg = sky2_pci_read32(hw, PCI_DEV_REG5);
		/* set all bits to 0 except bits 28 & 27 */
		reg &= P_CTL_TIM_VMAIN_AV_MSK;
		sky2_pci_write32(hw, PCI_DEV_REG5, reg);

		sky2_pci_write32(hw, PCI_CFG_REG_1, 0);

		sky2_write16(hw, B0_CTST, Y2_HW_WOL_ON);

		/* Enable workaround for dev 4.107 on Yukon-Ultra & Extreme */
		reg = sky2_read32(hw, B2_GP_IO);
		reg |= GLB_GPIO_STAT_RACE_DIS;
		sky2_write32(hw, B2_GP_IO, reg);

		sky2_read32(hw, B2_GP_IO);
	}

	/* Turn on "driver loaded" LED */
	sky2_write16(hw, B0_CTST, Y2_LED_STAT_ON);
}
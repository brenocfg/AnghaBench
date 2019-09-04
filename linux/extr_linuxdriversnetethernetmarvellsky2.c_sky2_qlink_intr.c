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
typedef  int u16 ;
struct sky2_port {int dummy; } ;
struct sky2_hw {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 int /*<<< orphan*/  PSM_CONFIG_REG4 ; 
 int /*<<< orphan*/  TST_CFG_WRITE_OFF ; 
 int /*<<< orphan*/  TST_CFG_WRITE_ON ; 
 int /*<<< orphan*/  Y2_IS_PHY_QLNK ; 
 struct sky2_port* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_link_up (struct sky2_port*) ; 
 int sky2_pci_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_qlink_intr(struct sky2_hw *hw)
{
	struct sky2_port *sky2 = netdev_priv(hw->dev[0]);
	u32 imask;
	u16 phy;

	/* disable irq */
	imask = sky2_read32(hw, B0_IMSK);
	imask &= ~Y2_IS_PHY_QLNK;
	sky2_write32(hw, B0_IMSK, imask);

	/* reset PHY Link Detect */
	phy = sky2_pci_read16(hw, PSM_CONFIG_REG4);
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	sky2_pci_write16(hw, PSM_CONFIG_REG4, phy | 1);
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

	sky2_link_up(sky2);
}
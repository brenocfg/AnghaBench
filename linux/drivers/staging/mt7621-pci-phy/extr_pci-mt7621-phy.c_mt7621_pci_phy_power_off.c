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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mt7621_pci_phy_instance {int index; } ;
struct mt7621_pci_phy {int dummy; } ;

/* Variables and functions */
 int RG_P0_TO_P1_WIDTH ; 
 int RG_PE1_FRC_PHY_EN ; 
 int RG_PE1_FRC_PHY_REG ; 
 int RG_PE1_PHY_EN ; 
 struct mt7621_pci_phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct mt7621_pci_phy_instance* phy_get_drvdata (struct phy*) ; 
 int phy_read (struct mt7621_pci_phy*,int) ; 
 int /*<<< orphan*/  phy_write (struct mt7621_pci_phy*,int,int) ; 

__attribute__((used)) static int mt7621_pci_phy_power_off(struct phy *phy)
{
	struct mt7621_pci_phy_instance *instance = phy_get_drvdata(phy);
	struct mt7621_pci_phy *mphy = dev_get_drvdata(phy->dev.parent);
	u32 offset = (instance->index != 1) ?
		RG_PE1_FRC_PHY_REG : RG_PE1_FRC_PHY_REG + RG_P0_TO_P1_WIDTH;
	u32 val;

	/* Disable PHY */
	val = phy_read(mphy, offset);
	val &= ~(RG_PE1_FRC_PHY_EN | RG_PE1_PHY_EN);
	val |= RG_PE1_FRC_PHY_EN;
	phy_write(mphy, val, offset);

	return 0;
}
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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct alx_hw {int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_speed; struct pci_dev* pdev; } ;

/* Variables and functions */
#define  ALX_GIGA_PSSR_1000MBS 130 
#define  ALX_GIGA_PSSR_100MBS 129 
#define  ALX_GIGA_PSSR_10MBS 128 
 int ALX_GIGA_PSSR_DPLX ; 
 int ALX_GIGA_PSSR_SPD_DPLX_RESOLVED ; 
 int ALX_GIGA_PSSR_SPEED ; 
 int /*<<< orphan*/  ALX_MII_GIGA_PSSR ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int alx_read_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

int alx_read_phy_link(struct alx_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	u16 bmsr, giga;
	int err;

	err = alx_read_phy_reg(hw, MII_BMSR, &bmsr);
	if (err)
		return err;

	err = alx_read_phy_reg(hw, MII_BMSR, &bmsr);
	if (err)
		return err;

	if (!(bmsr & BMSR_LSTATUS)) {
		hw->link_speed = SPEED_UNKNOWN;
		hw->duplex = DUPLEX_UNKNOWN;
		return 0;
	}

	/* speed/duplex result is saved in PHY Specific Status Register */
	err = alx_read_phy_reg(hw, ALX_MII_GIGA_PSSR, &giga);
	if (err)
		return err;

	if (!(giga & ALX_GIGA_PSSR_SPD_DPLX_RESOLVED))
		goto wrong_speed;

	switch (giga & ALX_GIGA_PSSR_SPEED) {
	case ALX_GIGA_PSSR_1000MBS:
		hw->link_speed = SPEED_1000;
		break;
	case ALX_GIGA_PSSR_100MBS:
		hw->link_speed = SPEED_100;
		break;
	case ALX_GIGA_PSSR_10MBS:
		hw->link_speed = SPEED_10;
		break;
	default:
		goto wrong_speed;
	}

	hw->duplex = (giga & ALX_GIGA_PSSR_DPLX) ? DUPLEX_FULL : DUPLEX_HALF;
	return 0;

wrong_speed:
	dev_err(&pdev->dev, "invalid PHY speed/duplex: 0x%x\n", giga);
	return -EINVAL;
}
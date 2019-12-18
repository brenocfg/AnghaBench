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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MV88E6XXX_PHY_PAGE ; 
 int mv88e6xxx_phy_page_get (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_phy_page_put (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_phy_write (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ) ; 

int mv88e6xxx_phy_page_write(struct mv88e6xxx_chip *chip, int phy,
			     u8 page, int reg, u16 val)
{
	int err;

	/* There is no paging for registers 22 */
	if (reg == MV88E6XXX_PHY_PAGE)
		return -EINVAL;

	err = mv88e6xxx_phy_page_get(chip, phy, page);
	if (!err) {
		err = mv88e6xxx_phy_write(chip, phy, MV88E6XXX_PHY_PAGE, page);
		if (!err)
			err = mv88e6xxx_phy_write(chip, phy, reg, val);

		mv88e6xxx_phy_page_put(chip, phy);
	}

	return err;
}
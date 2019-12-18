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
struct mii_bus {struct ag71xx* priv; } ;
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MII_CFG ; 
 int MII_CFG_RESET ; 
 int ag71xx_mdio_get_divider (struct ag71xx*,int*) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ag71xx_mdio_reset(struct mii_bus *bus)
{
	struct ag71xx *ag = bus->priv;
	int err;
	u32 t;

	err = ag71xx_mdio_get_divider(ag, &t);
	if (err)
		return err;

	ag71xx_wr(ag, AG71XX_REG_MII_CFG, t | MII_CFG_RESET);
	usleep_range(100, 200);

	ag71xx_wr(ag, AG71XX_REG_MII_CFG, t);
	usleep_range(100, 200);

	return 0;
}
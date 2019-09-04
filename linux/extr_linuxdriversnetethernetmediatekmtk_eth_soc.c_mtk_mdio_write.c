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
typedef  int /*<<< orphan*/  u16 ;
struct mtk_eth {int dummy; } ;
struct mii_bus {struct mtk_eth* priv; } ;

/* Variables and functions */
 int _mtk_mdio_write (struct mtk_eth*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdio_write(struct mii_bus *bus, int phy_addr,
			  int phy_reg, u16 val)
{
	struct mtk_eth *eth = bus->priv;

	return _mtk_mdio_write(eth, phy_addr, phy_reg, val);
}
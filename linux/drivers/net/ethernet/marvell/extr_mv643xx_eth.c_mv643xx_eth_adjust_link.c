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
struct net_device {TYPE_1__* phydev; } ;
struct mv643xx_eth_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int DISABLE_AUTO_NEG_FOR_DUPLEX ; 
 int DISABLE_AUTO_NEG_FOR_FLOW_CTRL ; 
 int DISABLE_AUTO_NEG_SPEED_GMII ; 
 scalar_t__ DUPLEX_FULL ; 
 int FORCE_LINK_PASS ; 
 int /*<<< orphan*/  PORT_SERIAL_CONTROL ; 
 int SET_FULL_DUPLEX_MODE ; 
 int SET_GMII_SPEED_TO_1000 ; 
 int SET_MII_SPEED_TO_100 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mv643xx_eth_adjust_link(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	u32 pscr = rdlp(mp, PORT_SERIAL_CONTROL);
	u32 autoneg_disable = FORCE_LINK_PASS |
	             DISABLE_AUTO_NEG_SPEED_GMII |
		     DISABLE_AUTO_NEG_FOR_FLOW_CTRL |
		     DISABLE_AUTO_NEG_FOR_DUPLEX;

	if (dev->phydev->autoneg == AUTONEG_ENABLE) {
		/* enable auto negotiation */
		pscr &= ~autoneg_disable;
		goto out_write;
	}

	pscr |= autoneg_disable;

	if (dev->phydev->speed == SPEED_1000) {
		/* force gigabit, half duplex not supported */
		pscr |= SET_GMII_SPEED_TO_1000;
		pscr |= SET_FULL_DUPLEX_MODE;
		goto out_write;
	}

	pscr &= ~SET_GMII_SPEED_TO_1000;

	if (dev->phydev->speed == SPEED_100)
		pscr |= SET_MII_SPEED_TO_100;
	else
		pscr &= ~SET_MII_SPEED_TO_100;

	if (dev->phydev->duplex == DUPLEX_FULL)
		pscr |= SET_FULL_DUPLEX_MODE;
	else
		pscr &= ~SET_FULL_DUPLEX_MODE;

out_write:
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);
}
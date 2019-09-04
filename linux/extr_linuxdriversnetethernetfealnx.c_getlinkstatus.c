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
struct netdev_private {int linkok; scalar_t__ PHYType; int /*<<< orphan*/ * phys; scalar_t__ mem; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BMCRSR ; 
 int BMSR_LSTATUS ; 
 int LinkIsUp2 ; 
 int /*<<< orphan*/  MII_BMSR ; 
 scalar_t__ MysonPHY ; 
 int ioread32 (scalar_t__) ; 
 int mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void getlinkstatus(struct net_device *dev)
/* function: Routine will read MII Status Register to get link status.       */
/* input   : dev... pointer to the adapter block.                            */
/* output  : none.                                                           */
{
	struct netdev_private *np = netdev_priv(dev);
	unsigned int i, DelayTime = 0x1000;

	np->linkok = 0;

	if (np->PHYType == MysonPHY) {
		for (i = 0; i < DelayTime; ++i) {
			if (ioread32(np->mem + BMCRSR) & LinkIsUp2) {
				np->linkok = 1;
				return;
			}
			udelay(100);
		}
	} else {
		for (i = 0; i < DelayTime; ++i) {
			if (mdio_read(dev, np->phys[0], MII_BMSR) & BMSR_LSTATUS) {
				np->linkok = 1;
				return;
			}
			udelay(100);
		}
	}
}
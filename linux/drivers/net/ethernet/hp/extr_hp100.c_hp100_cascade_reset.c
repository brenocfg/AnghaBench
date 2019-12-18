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
typedef  scalar_t__ u_short ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ HP100_CHIPID_LASSEN ; 
 int HP100_HW_RST ; 
 int /*<<< orphan*/  HP100_PCI_RESET ; 
 int HP100_RESET_LB ; 
 int HP100_SET_LB ; 
 int /*<<< orphan*/  HW_MAP ; 
 int /*<<< orphan*/  OPTION_LSW ; 
 int /*<<< orphan*/  PCICTRL2 ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_andb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_orb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hp100_cascade_reset(struct net_device *dev, u_short enable)
{
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4226, TRACE);
	printk("hp100: %s: cascade_reset\n", dev->name);
#endif

	if (enable) {
		hp100_outw(HP100_HW_RST | HP100_RESET_LB, OPTION_LSW);
		if (lp->chip == HP100_CHIPID_LASSEN) {
			/* Lassen requires a PCI transmit fifo reset */
			hp100_page(HW_MAP);
			hp100_andb(~HP100_PCI_RESET, PCICTRL2);
			hp100_orb(HP100_PCI_RESET, PCICTRL2);
			/* Wait for min. 300 ns */
			/* we can't use jiffies here, because it may be */
			/* that we have disabled the timer... */
			udelay(400);
			hp100_andb(~HP100_PCI_RESET, PCICTRL2);
			hp100_page(PERFORMANCE);
		}
	} else {		/* bring out of reset */
		hp100_outw(HP100_HW_RST | HP100_SET_LB, OPTION_LSW);
		udelay(400);
		hp100_page(PERFORMANCE);
	}
}
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
struct net_device {int /*<<< orphan*/  name; } ;
struct cpmac_priv {scalar_t__ regs; } ;

/* Variables and functions */
 int CPMAC_REG_END ; 
 int /*<<< orphan*/  cpmac_read (scalar_t__,int) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void cpmac_dump_regs(struct net_device *dev)
{
	int i;
	struct cpmac_priv *priv = netdev_priv(dev);

	for (i = 0; i < CPMAC_REG_END; i += 4) {
		if (i % 16 == 0) {
			if (i)
				printk("\n");
			printk("%s: reg[%p]:", dev->name, priv->regs + i);
		}
		printk(" %08x", cpmac_read(priv->regs, i));
	}
	printk("\n");
}
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
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void regdump(struct net_device *dev)
{
#ifdef DEBUG
	int ioaddr = dev->base_addr;
	int count;

	netdev_dbg(dev, "register dump:\n");
	for (count = 0; count < 16; count++) {
		if (!(count % 16))
			pr_cont("%04X:", ioaddr + count);
		pr_cont(" %02X", arcnet_inb(ioaddr, count));
	}
	pr_cont("\n");

	netdev_dbg(dev, "buffer0 dump:\n");
	/* set up the address register */
	count = 0;
	arcnet_outb((count >> 8) | RDDATAflag | AUTOINCflag,
		    ioaddr, com20020_REG_W_ADDR_HI);
	arcnet_outb(count & 0xff, ioaddr, COM20020_REG_W_ADDR_LO);

	for (count = 0; count < 256 + 32; count++) {
		if (!(count % 16))
			pr_cont("%04X:", count);

		/* copy the data */
		pr_cont(" %02X", arcnet_inb(ioaddr, COM20020_REG_RW_MEMDATA));
	}
	pr_cont("\n");
#endif
}
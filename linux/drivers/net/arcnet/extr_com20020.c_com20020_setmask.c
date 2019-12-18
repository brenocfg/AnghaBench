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
typedef  int /*<<< orphan*/  u_int ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM20020_REG_W_INTMASK ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcnet_outb (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void com20020_setmask(struct net_device *dev, int mask)
{
	u_int ioaddr = dev->base_addr;

	arc_printk(D_DURING, dev, "Setting mask to %x at %x\n", mask, ioaddr);
	arcnet_outb(mask, ioaddr, COM20020_REG_W_INTMASK);
}
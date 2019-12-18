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
struct net_device {int base_addr; } ;

/* Variables and functions */
 int AUTOINCflag ; 
 int /*<<< orphan*/  COM20020_REG_RW_MEMDATA ; 
 int /*<<< orphan*/  COM20020_REG_W_ADDR_HI ; 
 int /*<<< orphan*/  COM20020_REG_W_ADDR_LO ; 
 int /*<<< orphan*/  TIME (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcnet_outb (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcnet_outsb (int,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void com20020_copy_to_card(struct net_device *dev, int bufnum,
				  int offset, void *buf, int count)
{
	int ioaddr = dev->base_addr, ofs = 512 * bufnum + offset;

	/* set up the address register */
	arcnet_outb((ofs >> 8) | AUTOINCflag, ioaddr, COM20020_REG_W_ADDR_HI);
	arcnet_outb(ofs & 0xff, ioaddr, COM20020_REG_W_ADDR_LO);

	/* copy the data */
	TIME(dev, "outsb", count,
	     arcnet_outsb(ioaddr, COM20020_REG_RW_MEMDATA, buf, count));
}
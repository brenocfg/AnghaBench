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
 unsigned int AUTOINCflag ; 
 int /*<<< orphan*/  COM9026_REG_RW_MEMDATA ; 
 int /*<<< orphan*/  COM9026_REG_W_ADDR_HI ; 
 int /*<<< orphan*/  COM9026_REG_W_ADDR_LO ; 
 int /*<<< orphan*/  arcnet_inb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcnet_outb (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffer_byte (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_whole_buffer(struct net_device *dev, unsigned offset,
			     unsigned length, char *dest)
{
	int ioaddr = dev->base_addr;

	arcnet_outb((offset >> 8) | AUTOINCflag, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(offset & 0xff, ioaddr, COM9026_REG_W_ADDR_LO);

	while (length--)
#ifdef ONE_AT_A_TIME_RX
		*(dest++) = get_buffer_byte(dev, offset++);
#else
		*(dest++) = arcnet_inb(ioaddr, COM9026_REG_RW_MEMDATA);
#endif
}
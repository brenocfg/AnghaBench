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
struct net_device {long base_addr; } ;

/* Variables and functions */
 int inb (long) ; 
 int /*<<< orphan*/  outb (int,long) ; 

__attribute__((used)) static inline int set_holtek_fdx(struct net_device *dev)
{
	long ioaddr = dev->base_addr;

	outb(inb(ioaddr + 0x20) | 0x80, ioaddr + 0x20);
	return 0;
}
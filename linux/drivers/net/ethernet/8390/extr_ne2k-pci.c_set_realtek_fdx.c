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
 int E8390_NODMA ; 
 int E8390_PAGE0 ; 
 long NE_CMD ; 
 int /*<<< orphan*/  outb (int,long) ; 

__attribute__((used)) static inline int set_realtek_fdx(struct net_device *dev)
{
	long ioaddr = dev->base_addr;

	outb(0xC0 + E8390_NODMA, ioaddr + NE_CMD); /* Page 3 */
	outb(0xC0, ioaddr + 0x01); /* Enable writes to CONFIG3 */
	outb(0x40, ioaddr + 0x06); /* Enable full duplex */
	outb(0x00, ioaddr + 0x01); /* Disable writes to CONFIG3 */
	outb(E8390_PAGE0 + E8390_NODMA, ioaddr + NE_CMD); /* Page 0 */
	return 0;
}
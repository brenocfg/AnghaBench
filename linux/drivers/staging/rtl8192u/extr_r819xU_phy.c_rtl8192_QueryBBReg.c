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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ffs (int) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,int,int*) ; 

u32 rtl8192_QueryBBReg(struct net_device *dev, u32 reg_addr, u32 bitmask)
{
	u32 reg, bitshift;

	read_nic_dword(dev, reg_addr, &reg);
	bitshift = ffs(bitmask) - 1;

	return (reg & bitmask) >> bitshift;
}
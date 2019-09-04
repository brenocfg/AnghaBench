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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*,int,...) ; 
 int HW_LOCK_MAX_RESOURCE_VALUE ; 
 int MISC_REG_DRIVER_CONTROL_1 ; 
 int MISC_REG_DRIVER_CONTROL_7 ; 
 int NETIF_MSG_HW ; 
 int NETIF_MSG_IFUP ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 

__attribute__((used)) static bool bnx2x_trylock_hw_lock(struct bnx2x *bp, u32 resource)
{
	u32 lock_status;
	u32 resource_bit = (1 << resource);
	int func = BP_FUNC(bp);
	u32 hw_lock_control_reg;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "Trying to take a lock on resource %d\n", resource);

	/* Validating that the resource is within range */
	if (resource > HW_LOCK_MAX_RESOURCE_VALUE) {
		DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
		   "resource(0x%x) > HW_LOCK_MAX_RESOURCE_VALUE(0x%x)\n",
		   resource, HW_LOCK_MAX_RESOURCE_VALUE);
		return false;
	}

	if (func <= 5)
		hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
	else
		hw_lock_control_reg =
				(MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);

	/* Try to acquire the lock */
	REG_WR(bp, hw_lock_control_reg + 4, resource_bit);
	lock_status = REG_RD(bp, hw_lock_control_reg);
	if (lock_status & resource_bit)
		return true;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "Failed to get a lock on resource %d\n", resource);
	return false;
}
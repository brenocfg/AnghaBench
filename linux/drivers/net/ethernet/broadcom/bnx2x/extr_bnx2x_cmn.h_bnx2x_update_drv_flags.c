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
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_DRV_FLAGS ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  RESET_FLAGS (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SET_FLAGS (scalar_t__,scalar_t__) ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ SHMEM2_RD (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_flags ; 

__attribute__((used)) static inline void bnx2x_update_drv_flags(struct bnx2x *bp, u32 flags, u32 set)
{
	if (SHMEM2_HAS(bp, drv_flags)) {
		u32 drv_flags;
		bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_DRV_FLAGS);
		drv_flags = SHMEM2_RD(bp, drv_flags);

		if (set)
			SET_FLAGS(drv_flags, flags);
		else
			RESET_FLAGS(drv_flags, flags);

		SHMEM2_WR(bp, drv_flags, drv_flags);
		DP(NETIF_MSG_IFUP, "drv_flags 0x%08x\n", drv_flags);
		bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_DRV_FLAGS);
	}
}
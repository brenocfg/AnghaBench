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
struct bnx2x {unsigned long sp_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline bool bnx2x_wait_sp_comp(struct bnx2x *bp, unsigned long mask)
{
	int tout = 5000; /* Wait for 5 secs tops */

	while (tout--) {
		smp_mb();
		netif_addr_lock_bh(bp->dev);
		if (!(bp->sp_state & mask)) {
			netif_addr_unlock_bh(bp->dev);
			return true;
		}
		netif_addr_unlock_bh(bp->dev);

		usleep_range(1000, 2000);
	}

	smp_mb();

	netif_addr_lock_bh(bp->dev);
	if (bp->sp_state & mask) {
		BNX2X_ERR("Filtering completion timed out. sp_state 0x%lx, mask 0x%lx\n",
			  bp->sp_state, mask);
		netif_addr_unlock_bh(bp->dev);
		return false;
	}
	netif_addr_unlock_bh(bp->dev);

	return true;
}
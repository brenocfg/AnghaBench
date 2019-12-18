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
struct bnx2 {int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2_dump_ftq (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_dump_mcp_state (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_dump_state (struct bnx2*) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_tx_timeout(struct net_device *dev)
{
	struct bnx2 *bp = netdev_priv(dev);

	bnx2_dump_ftq(bp);
	bnx2_dump_state(bp);
	bnx2_dump_mcp_state(bp);

	/* This allows the netif to be shutdown gracefully before resetting */
	schedule_work(&bp->reset_task);
}
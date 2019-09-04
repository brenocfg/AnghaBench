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
struct bnxt {int /*<<< orphan*/  sp_event; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RESET_TASK_SP_EVENT ; 
 int /*<<< orphan*/  bnxt_queue_sp_work (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_tx_timeout(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);

	netdev_err(bp->dev,  "TX timeout detected, starting reset task!\n");
	set_bit(BNXT_RESET_TASK_SP_EVENT, &bp->sp_event);
	bnxt_queue_sp_work(bp);
}
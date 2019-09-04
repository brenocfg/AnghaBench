#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct bnx2 {int /*<<< orphan*/ * stats_blk; int /*<<< orphan*/ * status_blk; int /*<<< orphan*/  status_blk_mapping; int /*<<< orphan*/  status_stats_size; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bnx2_free_stats_blk(struct net_device *dev)
{
	struct bnx2 *bp = netdev_priv(dev);

	if (bp->status_blk) {
		dma_free_coherent(&bp->pdev->dev, bp->status_stats_size,
				  bp->status_blk,
				  bp->status_blk_mapping);
		bp->status_blk = NULL;
		bp->stats_blk = NULL;
	}
}
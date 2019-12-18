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
struct status_block {int dummy; } ;
struct statistics_block {int dummy; } ;
struct net_device {int dummy; } ;
struct bnx2 {int flags; int status_stats_size; scalar_t__ status_blk_mapping; scalar_t__ stats_blk_mapping; void* stats_blk; void* status_blk; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_FLAG_MSIX_CAP ; 
 int BNX2_MAX_MSIX_HW_VEC ; 
 int BNX2_SBLK_MSIX_ALIGN_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int L1_CACHE_ALIGN (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_alloc_stats_blk(struct net_device *dev)
{
	int status_blk_size;
	void *status_blk;
	struct bnx2 *bp = netdev_priv(dev);

	/* Combine status and statistics blocks into one allocation. */
	status_blk_size = L1_CACHE_ALIGN(sizeof(struct status_block));
	if (bp->flags & BNX2_FLAG_MSIX_CAP)
		status_blk_size = L1_CACHE_ALIGN(BNX2_MAX_MSIX_HW_VEC *
						 BNX2_SBLK_MSIX_ALIGN_SIZE);
	bp->status_stats_size = status_blk_size +
				sizeof(struct statistics_block);
	status_blk = dma_alloc_coherent(&bp->pdev->dev, bp->status_stats_size,
					&bp->status_blk_mapping, GFP_KERNEL);
	if (!status_blk)
		return -ENOMEM;

	bp->status_blk = status_blk;
	bp->stats_blk = status_blk + status_blk_size;
	bp->stats_blk_mapping = bp->status_blk_mapping + status_blk_size;

	return 0;
}
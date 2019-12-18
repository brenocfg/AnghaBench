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
struct rxdma_mailbox {int dummy; } ;
struct rx_ring_info {int rcr_table_size; int rbr_table_size; scalar_t__ rbr_pending; scalar_t__ rbr_index; scalar_t__ rbr; int /*<<< orphan*/  rbr_dma; scalar_t__ rcr_index; scalar_t__ rcr; int /*<<< orphan*/  rcr_dma; scalar_t__ mbox; int /*<<< orphan*/  mbox_dma; int /*<<< orphan*/  rxhash; } ;
struct page {int dummy; } ;
struct niu {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ (* alloc_coherent ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_RBR_RING_SIZE ; 
 int MAX_RCR_RING_SIZE ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_alloc_rx_ring_info(struct niu *np,
				  struct rx_ring_info *rp)
{
	BUILD_BUG_ON(sizeof(struct rxdma_mailbox) != 64);

	rp->rxhash = kcalloc(MAX_RBR_RING_SIZE, sizeof(struct page *),
			     GFP_KERNEL);
	if (!rp->rxhash)
		return -ENOMEM;

	rp->mbox = np->ops->alloc_coherent(np->device,
					   sizeof(struct rxdma_mailbox),
					   &rp->mbox_dma, GFP_KERNEL);
	if (!rp->mbox)
		return -ENOMEM;
	if ((unsigned long)rp->mbox & (64UL - 1)) {
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA mailbox %p\n",
			   rp->mbox);
		return -EINVAL;
	}

	rp->rcr = np->ops->alloc_coherent(np->device,
					  MAX_RCR_RING_SIZE * sizeof(__le64),
					  &rp->rcr_dma, GFP_KERNEL);
	if (!rp->rcr)
		return -ENOMEM;
	if ((unsigned long)rp->rcr & (64UL - 1)) {
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA RCR table %p\n",
			   rp->rcr);
		return -EINVAL;
	}
	rp->rcr_table_size = MAX_RCR_RING_SIZE;
	rp->rcr_index = 0;

	rp->rbr = np->ops->alloc_coherent(np->device,
					  MAX_RBR_RING_SIZE * sizeof(__le32),
					  &rp->rbr_dma, GFP_KERNEL);
	if (!rp->rbr)
		return -ENOMEM;
	if ((unsigned long)rp->rbr & (64UL - 1)) {
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA RBR table %p\n",
			   rp->rbr);
		return -EINVAL;
	}
	rp->rbr_table_size = MAX_RBR_RING_SIZE;
	rp->rbr_index = 0;
	rp->rbr_pending = 0;

	return 0;
}
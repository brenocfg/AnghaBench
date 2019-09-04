#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_ll2_buffer {int /*<<< orphan*/  list; int /*<<< orphan*/  data; int /*<<< orphan*/  phys_addr; } ;
struct qed_dev {TYPE_1__* ll2; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_cnt; int /*<<< orphan*/  rx_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_ll2_dealloc_buffer(struct qed_dev *cdev,
				 struct qed_ll2_buffer *buffer)
{
	spin_lock_bh(&cdev->ll2->lock);

	dma_unmap_single(&cdev->pdev->dev, buffer->phys_addr,
			 cdev->ll2->rx_size, DMA_FROM_DEVICE);
	kfree(buffer->data);
	list_del(&buffer->list);

	cdev->ll2->rx_cnt--;
	if (!cdev->ll2->rx_cnt)
		DP_INFO(cdev, "All LL2 entries were removed\n");

	spin_unlock_bh(&cdev->ll2->lock);

	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct qed_dev {TYPE_2__* pdev; TYPE_1__* ll2; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_SKB_PAD ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_ll2_alloc_buffer(struct qed_dev *cdev,
				u8 **data, dma_addr_t *phys_addr)
{
	*data = kmalloc(cdev->ll2->rx_size, GFP_ATOMIC);
	if (!(*data)) {
		DP_INFO(cdev, "Failed to allocate LL2 buffer data\n");
		return -ENOMEM;
	}

	*phys_addr = dma_map_single(&cdev->pdev->dev,
				    ((*data) + NET_SKB_PAD),
				    cdev->ll2->rx_size, DMA_FROM_DEVICE);
	if (dma_mapping_error(&cdev->pdev->dev, *phys_addr)) {
		DP_INFO(cdev, "Failed to map LL2 buffer data\n");
		kfree((*data));
		return -ENOMEM;
	}

	return 0;
}
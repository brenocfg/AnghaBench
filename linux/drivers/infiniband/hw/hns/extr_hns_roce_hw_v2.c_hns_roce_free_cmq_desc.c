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
struct hns_roce_v2_cmq_ring {int desc_num; int /*<<< orphan*/  desc; scalar_t__ desc_dma_addr; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_cmq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_free_cmq_desc(struct hns_roce_dev *hr_dev,
				   struct hns_roce_v2_cmq_ring *ring)
{
	dma_unmap_single(hr_dev->dev, ring->desc_dma_addr,
			 ring->desc_num * sizeof(struct hns_roce_cmq_desc),
			 DMA_BIDIRECTIONAL);

	ring->desc_dma_addr = 0;
	kfree(ring->desc);
}
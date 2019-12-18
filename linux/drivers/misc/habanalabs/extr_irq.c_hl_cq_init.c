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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct hl_cq {int /*<<< orphan*/  free_slots_cnt; scalar_t__ pi; scalar_t__ ci; int /*<<< orphan*/  hw_queue_id; scalar_t__ kernel_address; struct hl_device* hdev; int /*<<< orphan*/  bus_address; } ;
struct TYPE_2__ {void* (* asic_dma_alloc_coherent ) (struct hl_device*,scalar_t__,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  HL_CQ_LENGTH ; 
 scalar_t__ HL_CQ_SIZE_IN_BYTES ; 
 scalar_t__ HL_PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* stub1 (struct hl_device*,scalar_t__,int /*<<< orphan*/ *,int) ; 

int hl_cq_init(struct hl_device *hdev, struct hl_cq *q, u32 hw_queue_id)
{
	void *p;

	BUILD_BUG_ON(HL_CQ_SIZE_IN_BYTES > HL_PAGE_SIZE);

	p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, HL_CQ_SIZE_IN_BYTES,
				&q->bus_address, GFP_KERNEL | __GFP_ZERO);
	if (!p)
		return -ENOMEM;

	q->hdev = hdev;
	q->kernel_address = (u64) (uintptr_t) p;
	q->hw_queue_id = hw_queue_id;
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->free_slots_cnt, HL_CQ_LENGTH);

	return 0;
}
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
struct pvscsi_adapter {int req_pages; int req_depth; int cmp_pages; int msg_pages; int /*<<< orphan*/  msgRingPA; void* msg_ring; TYPE_1__* dev; int /*<<< orphan*/  use_msg; int /*<<< orphan*/  cmpRingPA; int /*<<< orphan*/  reqRingPA; int /*<<< orphan*/  ringStatePA; void* cmp_ring; void* req_ring; void* rings_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PVSCSI_MAX_NUM_PAGES_CMP_RING ; 
 int /*<<< orphan*/  PVSCSI_MAX_NUM_PAGES_MSG_RING ; 
 int /*<<< orphan*/  PVSCSI_MAX_NUM_PAGES_REQ_RING ; 
 int PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_msg_ring_pages ; 
 int /*<<< orphan*/  pvscsi_ring_pages ; 

__attribute__((used)) static int pvscsi_allocate_rings(struct pvscsi_adapter *adapter)
{
	adapter->rings_state = dma_alloc_coherent(&adapter->dev->dev, PAGE_SIZE,
			&adapter->ringStatePA, GFP_KERNEL);
	if (!adapter->rings_state)
		return -ENOMEM;

	adapter->req_pages = min(PVSCSI_MAX_NUM_PAGES_REQ_RING,
				 pvscsi_ring_pages);
	adapter->req_depth = adapter->req_pages
					* PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE;
	adapter->req_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->req_pages * PAGE_SIZE, &adapter->reqRingPA,
			GFP_KERNEL);
	if (!adapter->req_ring)
		return -ENOMEM;

	adapter->cmp_pages = min(PVSCSI_MAX_NUM_PAGES_CMP_RING,
				 pvscsi_ring_pages);
	adapter->cmp_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->cmp_pages * PAGE_SIZE, &adapter->cmpRingPA,
			GFP_KERNEL);
	if (!adapter->cmp_ring)
		return -ENOMEM;

	BUG_ON(!IS_ALIGNED(adapter->ringStatePA, PAGE_SIZE));
	BUG_ON(!IS_ALIGNED(adapter->reqRingPA, PAGE_SIZE));
	BUG_ON(!IS_ALIGNED(adapter->cmpRingPA, PAGE_SIZE));

	if (!adapter->use_msg)
		return 0;

	adapter->msg_pages = min(PVSCSI_MAX_NUM_PAGES_MSG_RING,
				 pvscsi_msg_ring_pages);
	adapter->msg_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->msg_pages * PAGE_SIZE, &adapter->msgRingPA,
			GFP_KERNEL);
	if (!adapter->msg_ring)
		return -ENOMEM;
	BUG_ON(!IS_ALIGNED(adapter->msgRingPA, PAGE_SIZE));

	return 0;
}
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
struct TYPE_2__ {scalar_t__ type; } ;
struct queue {unsigned long long sdma_id; TYPE_1__ properties; } ;
struct device_queue_manager {unsigned long long sdma_bitmap; unsigned long long xgmi_sdma_bitmap; } ;

/* Variables and functions */
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 unsigned long long get_num_sdma_queues (struct device_queue_manager*) ; 
 unsigned long long get_num_xgmi_sdma_queues (struct device_queue_manager*) ; 

__attribute__((used)) static void deallocate_sdma_queue(struct device_queue_manager *dqm,
				struct queue *q)
{
	if (q->properties.type == KFD_QUEUE_TYPE_SDMA) {
		if (q->sdma_id >= get_num_sdma_queues(dqm))
			return;
		dqm->sdma_bitmap |= (1ULL << q->sdma_id);
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		if (q->sdma_id >= get_num_xgmi_sdma_queues(dqm))
			return;
		dqm->xgmi_sdma_bitmap |= (1ULL << q->sdma_id);
	}
}
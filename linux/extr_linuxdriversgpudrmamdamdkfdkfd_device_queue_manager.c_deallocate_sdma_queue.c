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
struct device_queue_manager {int sdma_bitmap; } ;

/* Variables and functions */
 unsigned int get_num_sdma_queues (struct device_queue_manager*) ; 

__attribute__((used)) static void deallocate_sdma_queue(struct device_queue_manager *dqm,
				unsigned int sdma_queue_id)
{
	if (sdma_queue_id >= get_num_sdma_queues(dqm))
		return;
	dqm->sdma_bitmap |= (1 << sdma_queue_id);
}
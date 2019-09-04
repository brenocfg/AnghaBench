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
struct device_queue_manager {int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_QUEUE_TYPE_SDMA ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 int pm_send_unmap_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int unmap_sdma_queues(struct device_queue_manager *dqm,
				unsigned int sdma_engine)
{
	return pm_send_unmap_queue(&dqm->packets, KFD_QUEUE_TYPE_SDMA,
			KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0, false,
			sdma_engine);
}
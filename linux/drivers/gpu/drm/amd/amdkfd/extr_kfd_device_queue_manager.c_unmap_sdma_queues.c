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
struct device_queue_manager {int /*<<< orphan*/  packets; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* device_info; } ;
struct TYPE_3__ {int num_sdma_engines; int num_xgmi_sdma_engines; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_QUEUE_TYPE_SDMA ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 int pm_send_unmap_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int unmap_sdma_queues(struct device_queue_manager *dqm)
{
	int i, retval = 0;

	for (i = 0; i < dqm->dev->device_info->num_sdma_engines +
		dqm->dev->device_info->num_xgmi_sdma_engines; i++) {
		retval = pm_send_unmap_queue(&dqm->packets, KFD_QUEUE_TYPE_SDMA,
			KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0, false, i);
		if (retval)
			return retval;
	}
	return retval;
}
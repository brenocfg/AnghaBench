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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_queue_manager {int active_runlist; scalar_t__ sdma_queue_count; int /*<<< orphan*/  packets; int /*<<< orphan*/ * fence_addr; int /*<<< orphan*/  fence_gpu_addr; scalar_t__ xgmi_sdma_queue_count; scalar_t__ is_hws_hang; } ;
typedef  enum kfd_unmap_queues_filter { ____Placeholder_kfd_unmap_queues_filter } kfd_unmap_queues_filter ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KFD_FENCE_COMPLETED ; 
 int /*<<< orphan*/  KFD_FENCE_INIT ; 
 int /*<<< orphan*/  KFD_QUEUE_TYPE_COMPUTE ; 
 int amdkfd_fence_wait_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_release_ib (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_send_query_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_send_unmap_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  queue_preemption_timeout_ms ; 
 int /*<<< orphan*/  unmap_sdma_queues (struct device_queue_manager*) ; 

__attribute__((used)) static int unmap_queues_cpsch(struct device_queue_manager *dqm,
				enum kfd_unmap_queues_filter filter,
				uint32_t filter_param)
{
	int retval = 0;

	if (dqm->is_hws_hang)
		return -EIO;
	if (!dqm->active_runlist)
		return retval;

	pr_debug("Before destroying queues, sdma queue count is : %u, xgmi sdma queue count is : %u\n",
		dqm->sdma_queue_count, dqm->xgmi_sdma_queue_count);

	if (dqm->sdma_queue_count > 0 || dqm->xgmi_sdma_queue_count)
		unmap_sdma_queues(dqm);

	retval = pm_send_unmap_queue(&dqm->packets, KFD_QUEUE_TYPE_COMPUTE,
			filter, filter_param, false, 0);
	if (retval)
		return retval;

	*dqm->fence_addr = KFD_FENCE_INIT;
	pm_send_query_status(&dqm->packets, dqm->fence_gpu_addr,
				KFD_FENCE_COMPLETED);
	/* should be timed out */
	retval = amdkfd_fence_wait_timeout(dqm->fence_addr, KFD_FENCE_COMPLETED,
				queue_preemption_timeout_ms);
	if (retval)
		return retval;

	pm_release_ib(&dqm->packets);
	dqm->active_runlist = false;

	return retval;
}
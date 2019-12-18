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
struct device_queue_manager {int active_runlist; unsigned long long sdma_bitmap; unsigned long long xgmi_sdma_bitmap; int /*<<< orphan*/  hw_exception_work; scalar_t__ xgmi_sdma_queue_count; scalar_t__ sdma_queue_count; scalar_t__ processes_count; scalar_t__ queue_count; int /*<<< orphan*/  queues; int /*<<< orphan*/  lock_hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_num_sdma_queues (struct device_queue_manager*) ; 
 int get_num_xgmi_sdma_queues (struct device_queue_manager*) ; 
 int /*<<< orphan*/  get_pipes_per_mec (struct device_queue_manager*) ; 
 int /*<<< orphan*/  kfd_process_hw_exception ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int initialize_cpsch(struct device_queue_manager *dqm)
{
	pr_debug("num of pipes: %d\n", get_pipes_per_mec(dqm));

	mutex_init(&dqm->lock_hidden);
	INIT_LIST_HEAD(&dqm->queues);
	dqm->queue_count = dqm->processes_count = 0;
	dqm->sdma_queue_count = 0;
	dqm->xgmi_sdma_queue_count = 0;
	dqm->active_runlist = false;
	dqm->sdma_bitmap = ~0ULL >> (64 - get_num_sdma_queues(dqm));
	dqm->xgmi_sdma_bitmap = ~0ULL >> (64 - get_num_xgmi_sdma_queues(dqm));

	INIT_WORK(&dqm->hw_exception_work, kfd_process_hw_exception);

	return 0;
}
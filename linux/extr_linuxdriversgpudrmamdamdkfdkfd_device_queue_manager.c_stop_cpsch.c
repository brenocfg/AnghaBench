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
struct device_queue_manager {int /*<<< orphan*/  packets; int /*<<< orphan*/  fence_mem; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  kfd_gtt_sa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop_cpsch(struct device_queue_manager *dqm)
{
	dqm_lock(dqm);
	unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES, 0);
	dqm_unlock(dqm);

	kfd_gtt_sa_free(dqm->dev, dqm->fence_mem);
	pm_uninit(&dqm->packets);

	return 0;
}
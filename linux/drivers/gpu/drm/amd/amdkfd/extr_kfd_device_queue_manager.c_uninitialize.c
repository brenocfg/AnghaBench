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
struct device_queue_manager {scalar_t__ queue_count; scalar_t__ processes_count; int /*<<< orphan*/  pipeline_mem; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock_hidden; int /*<<< orphan*/ * mqd_mgrs; int /*<<< orphan*/  allocated_queues; } ;

/* Variables and functions */
 int KFD_MQD_TYPE_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfd_gtt_sa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninitialize(struct device_queue_manager *dqm)
{
	int i;

	WARN_ON(dqm->queue_count > 0 || dqm->processes_count > 0);

	kfree(dqm->allocated_queues);
	for (i = 0 ; i < KFD_MQD_TYPE_MAX ; i++)
		kfree(dqm->mqd_mgrs[i]);
	mutex_destroy(&dqm->lock_hidden);
	kfd_gtt_sa_free(dqm->dev, dqm->pipeline_mem);
}
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
struct queue {int dummy; } ;
struct qcm_process_device {int dummy; } ;
struct device_queue_manager {int dummy; } ;

/* Variables and functions */
 int destroy_queue_nocpsch_locked (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 

__attribute__((used)) static int destroy_queue_nocpsch(struct device_queue_manager *dqm,
				struct qcm_process_device *qpd,
				struct queue *q)
{
	int retval;

	dqm_lock(dqm);
	retval = destroy_queue_nocpsch_locked(dqm, qpd, q);
	dqm_unlock(dqm);

	return retval;
}
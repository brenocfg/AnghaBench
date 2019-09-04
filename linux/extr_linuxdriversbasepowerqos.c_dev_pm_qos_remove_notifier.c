#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct TYPE_5__ {TYPE_3__* qos; } ;
struct device {TYPE_2__ power; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifiers; } ;
struct TYPE_6__ {TYPE_1__ resume_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_3__*) ; 
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ ,struct notifier_block*) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dev_pm_qos_remove_notifier(struct device *dev,
			       struct notifier_block *notifier)
{
	int retval = 0;

	mutex_lock(&dev_pm_qos_mtx);

	/* Silently return if the constraints object is not present. */
	if (!IS_ERR_OR_NULL(dev->power.qos))
		retval = blocking_notifier_chain_unregister(dev->power.qos->resume_latency.notifiers,
							    notifier);

	mutex_unlock(&dev_pm_qos_mtx);
	return retval;
}
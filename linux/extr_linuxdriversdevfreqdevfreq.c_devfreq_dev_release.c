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
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct devfreq {int /*<<< orphan*/  lock; TYPE_3__ dev; TYPE_2__* profile; TYPE_1__* governor; int /*<<< orphan*/  node; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_STOP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devfreq_list_lock ; 
 int /*<<< orphan*/  find_device_devfreq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devfreq*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static void devfreq_dev_release(struct device *dev)
{
	struct devfreq *devfreq = to_devfreq(dev);

	mutex_lock(&devfreq_list_lock);
	if (IS_ERR(find_device_devfreq(devfreq->dev.parent))) {
		mutex_unlock(&devfreq_list_lock);
		dev_warn(&devfreq->dev, "releasing devfreq which doesn't exist\n");
		return;
	}
	list_del(&devfreq->node);
	mutex_unlock(&devfreq_list_lock);

	if (devfreq->governor)
		devfreq->governor->event_handler(devfreq,
						 DEVFREQ_GOV_STOP, NULL);

	if (devfreq->profile->exit)
		devfreq->profile->exit(devfreq->dev.parent);

	mutex_destroy(&devfreq->lock);
	kfree(devfreq);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {TYPE_1__* asd; struct v4l2_async_notifier* notifier; int /*<<< orphan*/ * subdev_notifier; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  waiting; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_cleanup (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_call_unbind (struct v4l2_async_notifier*,struct v4l2_subdev*,TYPE_1__*) ; 

void v4l2_async_unregister_subdev(struct v4l2_subdev *sd)
{
	mutex_lock(&list_lock);

	__v4l2_async_notifier_unregister(sd->subdev_notifier);
	__v4l2_async_notifier_cleanup(sd->subdev_notifier);
	kfree(sd->subdev_notifier);
	sd->subdev_notifier = NULL;

	if (sd->asd) {
		struct v4l2_async_notifier *notifier = sd->notifier;

		list_add(&sd->asd->list, &notifier->waiting);

		v4l2_async_notifier_call_unbind(notifier, sd, sd->asd);
	}

	v4l2_async_cleanup(sd);

	mutex_unlock(&list_lock);
}
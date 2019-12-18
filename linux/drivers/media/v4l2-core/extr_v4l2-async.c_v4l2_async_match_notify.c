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
struct v4l2_subdev {int /*<<< orphan*/  async_list; struct v4l2_async_notifier* notifier; struct v4l2_async_subdev* asd; } ;
struct v4l2_device {int dummy; } ;
struct v4l2_async_subdev {int /*<<< orphan*/  list; } ;
struct v4l2_async_notifier {struct v4l2_async_notifier* parent; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct v4l2_async_notifier* v4l2_async_find_subdev_notifier (struct v4l2_subdev*) ; 
 int v4l2_async_notifier_call_bound (struct v4l2_async_notifier*,struct v4l2_subdev*,struct v4l2_async_subdev*) ; 
 int v4l2_async_notifier_try_all_subdevs (struct v4l2_async_notifier*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int v4l2_async_match_notify(struct v4l2_async_notifier *notifier,
				   struct v4l2_device *v4l2_dev,
				   struct v4l2_subdev *sd,
				   struct v4l2_async_subdev *asd)
{
	struct v4l2_async_notifier *subdev_notifier;
	int ret;

	ret = v4l2_device_register_subdev(v4l2_dev, sd);
	if (ret < 0)
		return ret;

	ret = v4l2_async_notifier_call_bound(notifier, sd, asd);
	if (ret < 0) {
		v4l2_device_unregister_subdev(sd);
		return ret;
	}

	/* Remove from the waiting list */
	list_del(&asd->list);
	sd->asd = asd;
	sd->notifier = notifier;

	/* Move from the global subdevice list to notifier's done */
	list_move(&sd->async_list, &notifier->done);

	/*
	 * See if the sub-device has a notifier. If not, return here.
	 */
	subdev_notifier = v4l2_async_find_subdev_notifier(sd);
	if (!subdev_notifier || subdev_notifier->parent)
		return 0;

	/*
	 * Proceed with checking for the sub-device notifier's async
	 * sub-devices, and return the result. The error will be handled by the
	 * caller.
	 */
	subdev_notifier->parent = notifier;

	return v4l2_async_notifier_try_all_subdevs(subdev_notifier);
}
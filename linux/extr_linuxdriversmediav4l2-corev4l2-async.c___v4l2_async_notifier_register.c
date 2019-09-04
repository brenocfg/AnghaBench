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
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {int match_type; int /*<<< orphan*/  list; TYPE_2__ match; } ;
struct v4l2_async_notifier {int num_subdevs; int /*<<< orphan*/  list; int /*<<< orphan*/  waiting; struct v4l2_async_subdev** subdevs; int /*<<< orphan*/  done; TYPE_1__* v4l2_dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  V4L2_ASYNC_MATCH_CUSTOM 131 
#define  V4L2_ASYNC_MATCH_DEVNAME 130 
#define  V4L2_ASYNC_MATCH_FWNODE 129 
#define  V4L2_ASYNC_MATCH_I2C 128 
 int V4L2_MAX_SUBDEVS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notifier_list ; 
 int /*<<< orphan*/  v4l2_async_notifier_fwnode_has_async_subdev (struct v4l2_async_notifier*,int /*<<< orphan*/ ,int) ; 
 int v4l2_async_notifier_try_all_subdevs (struct v4l2_async_notifier*) ; 
 int v4l2_async_notifier_try_complete (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unbind_all_subdevs (struct v4l2_async_notifier*) ; 

__attribute__((used)) static int __v4l2_async_notifier_register(struct v4l2_async_notifier *notifier)
{
	struct device *dev =
		notifier->v4l2_dev ? notifier->v4l2_dev->dev : NULL;
	struct v4l2_async_subdev *asd;
	int ret;
	int i;

	if (notifier->num_subdevs > V4L2_MAX_SUBDEVS)
		return -EINVAL;

	INIT_LIST_HEAD(&notifier->waiting);
	INIT_LIST_HEAD(&notifier->done);

	mutex_lock(&list_lock);

	for (i = 0; i < notifier->num_subdevs; i++) {
		asd = notifier->subdevs[i];

		switch (asd->match_type) {
		case V4L2_ASYNC_MATCH_CUSTOM:
		case V4L2_ASYNC_MATCH_DEVNAME:
		case V4L2_ASYNC_MATCH_I2C:
			break;
		case V4L2_ASYNC_MATCH_FWNODE:
			if (v4l2_async_notifier_fwnode_has_async_subdev(
				    notifier, asd->match.fwnode, i)) {
				dev_err(dev,
					"fwnode has already been registered or in notifier's subdev list\n");
				ret = -EEXIST;
				goto err_unlock;
			}
			break;
		default:
			dev_err(dev, "Invalid match type %u on %p\n",
				asd->match_type, asd);
			ret = -EINVAL;
			goto err_unlock;
		}
		list_add_tail(&asd->list, &notifier->waiting);
	}

	ret = v4l2_async_notifier_try_all_subdevs(notifier);
	if (ret < 0)
		goto err_unbind;

	ret = v4l2_async_notifier_try_complete(notifier);
	if (ret < 0)
		goto err_unbind;

	/* Keep also completed notifiers on the list */
	list_add(&notifier->list, &notifier_list);

	mutex_unlock(&list_lock);

	return 0;

err_unbind:
	/*
	 * On failure, unbind all sub-devices registered through this notifier.
	 */
	v4l2_async_notifier_unbind_all_subdevs(notifier);

err_unlock:
	mutex_unlock(&list_lock);

	return ret;
}
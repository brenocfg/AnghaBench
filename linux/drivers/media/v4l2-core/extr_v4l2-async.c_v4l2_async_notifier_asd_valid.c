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
struct v4l2_async_subdev {int match_type; } ;
struct v4l2_async_notifier {TYPE_1__* v4l2_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
#define  V4L2_ASYNC_MATCH_CUSTOM 131 
#define  V4L2_ASYNC_MATCH_DEVNAME 130 
#define  V4L2_ASYNC_MATCH_FWNODE 129 
#define  V4L2_ASYNC_MATCH_I2C 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,struct v4l2_async_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_has_async_subdev (struct v4l2_async_notifier*,struct v4l2_async_subdev*,int) ; 

__attribute__((used)) static int v4l2_async_notifier_asd_valid(struct v4l2_async_notifier *notifier,
					 struct v4l2_async_subdev *asd,
					 int this_index)
{
	struct device *dev =
		notifier->v4l2_dev ? notifier->v4l2_dev->dev : NULL;

	if (!asd)
		return -EINVAL;

	switch (asd->match_type) {
	case V4L2_ASYNC_MATCH_CUSTOM:
	case V4L2_ASYNC_MATCH_DEVNAME:
	case V4L2_ASYNC_MATCH_I2C:
	case V4L2_ASYNC_MATCH_FWNODE:
		if (v4l2_async_notifier_has_async_subdev(notifier, asd,
							 this_index)) {
			dev_dbg(dev, "subdev descriptor already listed in this or other notifiers\n");
			return -EEXIST;
		}
		break;
	default:
		dev_err(dev, "Invalid match type %u on %p\n",
			asd->match_type, asd);
		return -EINVAL;
	}

	return 0;
}
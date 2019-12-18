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
struct v4l2_subdev {struct v4l2_async_notifier* subdev_notifier; int /*<<< orphan*/  dev; } ;
struct v4l2_async_notifier {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct v4l2_async_notifier*) ; 
 struct v4l2_async_notifier* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (struct v4l2_async_notifier*) ; 
 int v4l2_async_notifier_parse_fwnode_sensor_common (int /*<<< orphan*/ ,struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (struct v4l2_async_notifier*) ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int v4l2_async_subdev_notifier_register (struct v4l2_subdev*,struct v4l2_async_notifier*) ; 

int v4l2_async_register_subdev_sensor_common(struct v4l2_subdev *sd)
{
	struct v4l2_async_notifier *notifier;
	int ret;

	if (WARN_ON(!sd->dev))
		return -ENODEV;

	notifier = kzalloc(sizeof(*notifier), GFP_KERNEL);
	if (!notifier)
		return -ENOMEM;

	v4l2_async_notifier_init(notifier);

	ret = v4l2_async_notifier_parse_fwnode_sensor_common(sd->dev,
							     notifier);
	if (ret < 0)
		goto out_cleanup;

	ret = v4l2_async_subdev_notifier_register(sd, notifier);
	if (ret < 0)
		goto out_cleanup;

	ret = v4l2_async_register_subdev(sd);
	if (ret < 0)
		goto out_unregister;

	sd->subdev_notifier = notifier;

	return 0;

out_unregister:
	v4l2_async_notifier_unregister(notifier);

out_cleanup:
	v4l2_async_notifier_cleanup(notifier);
	kfree(notifier);

	return ret;
}
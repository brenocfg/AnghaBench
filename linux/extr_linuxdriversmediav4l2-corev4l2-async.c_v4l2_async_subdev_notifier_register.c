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
struct v4l2_subdev {int dummy; } ;
struct v4l2_async_notifier {struct v4l2_subdev* sd; scalar_t__ v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int __v4l2_async_notifier_register (struct v4l2_async_notifier*) ; 

int v4l2_async_subdev_notifier_register(struct v4l2_subdev *sd,
					struct v4l2_async_notifier *notifier)
{
	int ret;

	if (WARN_ON(!sd || notifier->v4l2_dev))
		return -EINVAL;

	notifier->sd = sd;

	ret = __v4l2_async_notifier_register(notifier);
	if (ret)
		notifier->sd = NULL;

	return ret;
}
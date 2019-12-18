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
struct v4l2_device {int dummy; } ;
struct v4l2_async_notifier {struct v4l2_device* v4l2_dev; scalar_t__ sd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int __v4l2_async_notifier_register (struct v4l2_async_notifier*) ; 

int v4l2_async_notifier_register(struct v4l2_device *v4l2_dev,
				 struct v4l2_async_notifier *notifier)
{
	int ret;

	if (WARN_ON(!v4l2_dev || notifier->sd))
		return -EINVAL;

	notifier->v4l2_dev = v4l2_dev;

	ret = __v4l2_async_notifier_register(notifier);
	if (ret)
		notifier->v4l2_dev = NULL;

	return ret;
}
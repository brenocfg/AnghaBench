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
struct v4l2_async_notifier {struct v4l2_device* v4l2_dev; struct v4l2_async_notifier* parent; } ;

/* Variables and functions */

__attribute__((used)) static struct v4l2_device *v4l2_async_notifier_find_v4l2_dev(
	struct v4l2_async_notifier *notifier)
{
	while (notifier->parent)
		notifier = notifier->parent;

	return notifier->v4l2_dev;
}
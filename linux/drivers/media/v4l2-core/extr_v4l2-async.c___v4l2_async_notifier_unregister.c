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
struct v4l2_async_notifier {int /*<<< orphan*/  list; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unbind_all_subdevs (struct v4l2_async_notifier*) ; 

__attribute__((used)) static void
__v4l2_async_notifier_unregister(struct v4l2_async_notifier *notifier)
{
	if (!notifier || (!notifier->v4l2_dev && !notifier->sd))
		return;

	v4l2_async_notifier_unbind_all_subdevs(notifier);

	notifier->sd = NULL;
	notifier->v4l2_dev = NULL;

	list_del(&notifier->list);
}
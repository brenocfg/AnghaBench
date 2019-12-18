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
struct v4l2_async_notifier {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_async_notifier_cleanup (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void v4l2_async_notifier_cleanup(struct v4l2_async_notifier *notifier)
{
	mutex_lock(&list_lock);

	__v4l2_async_notifier_cleanup(notifier);

	mutex_unlock(&list_lock);
}
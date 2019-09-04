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
struct cio2_device {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cio2_notifier_exit(struct cio2_device *cio2)
{
	v4l2_async_notifier_unregister(&cio2->notifier);
	v4l2_async_notifier_cleanup(&cio2->notifier);
}
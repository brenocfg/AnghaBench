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

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_response_mutex ; 
 int /*<<< orphan*/  xs_suspend_exit () ; 
 int /*<<< orphan*/  xs_watch_rwsem ; 

void xs_suspend_cancel(void)
{
	mutex_unlock(&xs_response_mutex);
	up_write(&xs_watch_rwsem);

	xs_suspend_exit();
}
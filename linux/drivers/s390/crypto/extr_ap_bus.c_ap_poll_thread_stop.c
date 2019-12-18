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
 int /*<<< orphan*/ * ap_poll_kthread ; 
 int /*<<< orphan*/  ap_poll_thread_mutex ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ap_poll_thread_stop(void)
{
	if (!ap_poll_kthread)
		return;
	mutex_lock(&ap_poll_thread_mutex);
	kthread_stop(ap_poll_kthread);
	ap_poll_kthread = NULL;
	mutex_unlock(&ap_poll_thread_mutex);
}
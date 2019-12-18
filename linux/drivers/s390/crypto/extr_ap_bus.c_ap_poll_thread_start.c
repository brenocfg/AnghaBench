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
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ap_poll_kthread ; 
 int /*<<< orphan*/  ap_poll_thread ; 
 int /*<<< orphan*/  ap_poll_thread_mutex ; 
 scalar_t__ ap_using_interrupts () ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ap_poll_thread_start(void)
{
	int rc;

	if (ap_using_interrupts() || ap_poll_kthread)
		return 0;
	mutex_lock(&ap_poll_thread_mutex);
	ap_poll_kthread = kthread_run(ap_poll_thread, NULL, "appoll");
	rc = PTR_ERR_OR_ZERO(ap_poll_kthread);
	if (rc)
		ap_poll_kthread = NULL;
	mutex_unlock(&ap_poll_thread_mutex);
	return rc;
}
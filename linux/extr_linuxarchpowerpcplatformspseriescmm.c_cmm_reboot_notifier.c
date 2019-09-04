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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 unsigned long SYS_RESTART ; 
 int /*<<< orphan*/  cmm_free_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmm_thread_ptr ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loaned_pages ; 

__attribute__((used)) static int cmm_reboot_notifier(struct notifier_block *nb,
			       unsigned long action, void *unused)
{
	if (action == SYS_RESTART) {
		if (cmm_thread_ptr)
			kthread_stop(cmm_thread_ptr);
		cmm_thread_ptr = NULL;
		cmm_free_pages(loaned_pages);
	}
	return NOTIFY_DONE;
}
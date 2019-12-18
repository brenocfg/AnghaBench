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
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_context_cleaned_flag ; 
 int /*<<< orphan*/  pvr2_context_cleanup_data ; 
 int pvr2_context_cleanup_flag ; 
 int /*<<< orphan*/  pvr2_context_sync_data ; 
 int /*<<< orphan*/  pvr2_context_thread_ptr ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void pvr2_context_global_done(void)
{
	pvr2_context_cleanup_flag = !0;
	wake_up(&pvr2_context_sync_data);
	wait_event_interruptible(
		pvr2_context_cleanup_data,
		pvr2_context_cleaned_flag);
	kthread_stop(pvr2_context_thread_ptr);
}
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
struct pvr2_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_CTXT ; 
 int kthread_should_stop () ; 
 int /*<<< orphan*/  pvr2_context_check (struct pvr2_context*) ; 
 int pvr2_context_cleaned_flag ; 
 int /*<<< orphan*/  pvr2_context_cleanup_data ; 
 struct pvr2_context* pvr2_context_notify_first ; 
 int /*<<< orphan*/  pvr2_context_set_notify (struct pvr2_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_context_shutok () ; 
 int /*<<< orphan*/  pvr2_context_sync_data ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvr2_context_thread_func(void *foo)
{
	struct pvr2_context *mp;

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread start");

	do {
		while ((mp = pvr2_context_notify_first) != NULL) {
			pvr2_context_set_notify(mp, 0);
			pvr2_context_check(mp);
		}
		wait_event_interruptible(
			pvr2_context_sync_data,
			((pvr2_context_notify_first != NULL) ||
			 pvr2_context_shutok()));
	} while (!pvr2_context_shutok());

	pvr2_context_cleaned_flag = !0;
	wake_up(&pvr2_context_cleanup_data);

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread cleaned up");

	wait_event_interruptible(
		pvr2_context_sync_data,
		kthread_should_stop());

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread end");

	return 0;
}
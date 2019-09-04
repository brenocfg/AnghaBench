#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int secs; long nsecs; void* system_time; } ;
struct TYPE_6__ {int secs; long nsecs; void* system_time; scalar_t__ mbz; } ;
struct TYPE_8__ {TYPE_3__ settime32; TYPE_2__ settime64; } ;
struct xen_platform_op {TYPE_4__ u; int /*<<< orphan*/  cmd; } ;
struct timespec64 {int tv_sec; long tv_nsec; } ;
struct TYPE_5__ {int xtime_nsec; int shift; } ;
struct timekeeper {int xtime_sec; TYPE_1__ tkr_mono; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int HYPERVISOR_platform_op (struct xen_platform_op*) ; 
 int NOTIFY_BAD ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  XENPF_settime32 ; 
 int /*<<< orphan*/  XENPF_settime64 ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 
 void* xen_clocksource_read () ; 

__attribute__((used)) static int xen_pvclock_gtod_notify(struct notifier_block *nb,
				   unsigned long was_set, void *priv)
{
	/* Protected by the calling core code serialization */
	static struct timespec64 next_sync;

	struct xen_platform_op op;
	struct timespec64 now;
	struct timekeeper *tk = priv;
	static bool settime64_supported = true;
	int ret;

	now.tv_sec = tk->xtime_sec;
	now.tv_nsec = (long)(tk->tkr_mono.xtime_nsec >> tk->tkr_mono.shift);

	/*
	 * We only take the expensive HV call when the clock was set
	 * or when the 11 minutes RTC synchronization time elapsed.
	 */
	if (!was_set && timespec64_compare(&now, &next_sync) < 0)
		return NOTIFY_OK;

again:
	if (settime64_supported) {
		op.cmd = XENPF_settime64;
		op.u.settime64.mbz = 0;
		op.u.settime64.secs = now.tv_sec;
		op.u.settime64.nsecs = now.tv_nsec;
		op.u.settime64.system_time = xen_clocksource_read();
	} else {
		op.cmd = XENPF_settime32;
		op.u.settime32.secs = now.tv_sec;
		op.u.settime32.nsecs = now.tv_nsec;
		op.u.settime32.system_time = xen_clocksource_read();
	}

	ret = HYPERVISOR_platform_op(&op);

	if (ret == -ENOSYS && settime64_supported) {
		settime64_supported = false;
		goto again;
	}
	if (ret < 0)
		return NOTIFY_BAD;

	/*
	 * Move the next drift compensation time 11 minutes
	 * ahead. That's emulating the sync_cmos_clock() update for
	 * the hardware RTC.
	 */
	next_sync = now;
	next_sync.tv_sec += 11 * 60;

	return NOTIFY_OK;
}
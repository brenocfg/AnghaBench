#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int secs; long nsecs; int /*<<< orphan*/  system_time; scalar_t__ mbz; } ;
struct TYPE_6__ {TYPE_2__ settime64; } ;
struct xen_platform_op {TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct timespec64 {int tv_sec; long tv_nsec; } ;
struct TYPE_4__ {int xtime_nsec; int shift; } ;
struct timekeeper {int xtime_sec; int /*<<< orphan*/  wall_to_monotonic; TYPE_1__ tkr_mono; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERVISOR_platform_op (struct xen_platform_op*) ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  XENPF_settime64 ; 
 struct timespec64 timespec64_add (struct timespec64,int /*<<< orphan*/ ) ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 
 int /*<<< orphan*/  timespec64_to_ns (struct timespec64*) ; 

__attribute__((used)) static int xen_pvclock_gtod_notify(struct notifier_block *nb,
				   unsigned long was_set, void *priv)
{
	/* Protected by the calling core code serialization */
	static struct timespec64 next_sync;

	struct xen_platform_op op;
	struct timespec64 now, system_time;
	struct timekeeper *tk = priv;

	now.tv_sec = tk->xtime_sec;
	now.tv_nsec = (long)(tk->tkr_mono.xtime_nsec >> tk->tkr_mono.shift);
	system_time = timespec64_add(now, tk->wall_to_monotonic);

	/*
	 * We only take the expensive HV call when the clock was set
	 * or when the 11 minutes RTC synchronization time elapsed.
	 */
	if (!was_set && timespec64_compare(&now, &next_sync) < 0)
		return NOTIFY_OK;

	op.cmd = XENPF_settime64;
	op.u.settime64.mbz = 0;
	op.u.settime64.secs = now.tv_sec;
	op.u.settime64.nsecs = now.tv_nsec;
	op.u.settime64.system_time = timespec64_to_ns(&system_time);
	(void)HYPERVISOR_platform_op(&op);

	/*
	 * Move the next drift compensation time 11 minutes
	 * ahead. That's emulating the sync_cmos_clock() update for
	 * the hardware RTC.
	 */
	next_sync = now;
	next_sync.tv_sec += 11 * 60;

	return NOTIFY_OK;
}
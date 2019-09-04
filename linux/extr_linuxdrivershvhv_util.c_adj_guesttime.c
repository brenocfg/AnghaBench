#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u64 ;
struct TYPE_5__ {int /*<<< orphan*/  lock; void* host_time; void* ref_time; } ;
struct TYPE_4__ {void* (* read ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ICTIMESYNCFLAG_SYNC ; 
 int /*<<< orphan*/  adj_time_work ; 
 TYPE_3__ host_ts ; 
 TYPE_1__* hyperv_cs ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* stub1 (TYPE_1__*) ; 

__attribute__((used)) static inline void adj_guesttime(u64 hosttime, u64 reftime, u8 adj_flags)
{
	unsigned long flags;
	u64 cur_reftime;

	/*
	 * Save the adjusted time sample from the host and the snapshot
	 * of the current system time.
	 */
	spin_lock_irqsave(&host_ts.lock, flags);

	cur_reftime = hyperv_cs->read(hyperv_cs);
	host_ts.host_time = hosttime;
	host_ts.ref_time = cur_reftime;

	/*
	 * TimeSync v4 messages contain reference time (guest's Hyper-V
	 * clocksource read when the time sample was generated), we can
	 * improve the precision by adding the delta between now and the
	 * time of generation. For older protocols we set
	 * reftime == cur_reftime on call.
	 */
	host_ts.host_time += (cur_reftime - reftime);

	spin_unlock_irqrestore(&host_ts.lock, flags);

	/* Schedule work to do do_settimeofday64() */
	if (adj_flags & ICTIMESYNCFLAG_SYNC)
		schedule_work(&adj_time_work);
}
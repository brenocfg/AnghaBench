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
typedef  int /*<<< orphan*/  u_long ;
typedef  unsigned short u16 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 unsigned short iclock_count ; 
 int /*<<< orphan*/  iclock_lock ; 
 int /*<<< orphan*/  iclock_timestamp ; 
 unsigned short ktime_divns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned short
mISDN_clock_get(void)
{
	u_long		flags;
	ktime_t		timestamp_now;
	u16		delta;
	u16		count;

	read_lock_irqsave(&iclock_lock, flags);
	/* calc elapsed time by system clock */
	timestamp_now = ktime_get();
	delta = ktime_divns(ktime_sub(timestamp_now, iclock_timestamp),
			(NSEC_PER_SEC / 8000));
	/* add elapsed time to counter */
	count =	iclock_count + delta;
	read_unlock_irqrestore(&iclock_lock, flags);
	return count;
}
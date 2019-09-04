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
typedef  scalar_t__ time64_t ;
struct timespec64 {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TIME_CMD ; 
 int /*<<< orphan*/  rtc_end_op () ; 
 int /*<<< orphan*/  rtc_init_op () ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_write_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_write_word (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int update_persistent_clock64(struct timespec64 now)
{
	time64_t time = now.tv_sec;
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);
	rtc_init_op();
	rtc_write_byte(SET_TIME_CMD);
	/*
	 * Due to the hardware limitation, we cast to 'unsigned long' type,
	 * so it will overflow in year 2106 on 32-bit machine.
	 */
	rtc_write_word((unsigned long)time);
	rtc_end_op();
	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}
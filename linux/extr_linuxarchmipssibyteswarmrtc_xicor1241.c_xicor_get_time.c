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
typedef  int /*<<< orphan*/  time64_t ;

/* Variables and functions */
 int /*<<< orphan*/  X1241REG_DT ; 
 int /*<<< orphan*/  X1241REG_HR ; 
 unsigned int X1241REG_HR_MIL ; 
 int /*<<< orphan*/  X1241REG_MN ; 
 int /*<<< orphan*/  X1241REG_MO ; 
 int /*<<< orphan*/  X1241REG_SC ; 
 int /*<<< orphan*/  X1241REG_Y2K ; 
 int /*<<< orphan*/  X1241REG_YR ; 
 unsigned int bcd2bin (unsigned int) ; 
 int /*<<< orphan*/  mktime64 (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int xicor_read (int /*<<< orphan*/ ) ; 

time64_t xicor_get_time(void)
{
	unsigned int year, mon, day, hour, min, sec, y2k;
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);
	sec = xicor_read(X1241REG_SC);
	min = xicor_read(X1241REG_MN);
	hour = xicor_read(X1241REG_HR);

	if (hour & X1241REG_HR_MIL) {
		hour &= 0x3f;
	} else {
		if (hour & 0x20)
			hour = (hour & 0xf) + 0x12;
	}

	day = xicor_read(X1241REG_DT);
	mon = xicor_read(X1241REG_MO);
	year = xicor_read(X1241REG_YR);
	y2k = xicor_read(X1241REG_Y2K);
	spin_unlock_irqrestore(&rtc_lock, flags);

	sec = bcd2bin(sec);
	min = bcd2bin(min);
	hour = bcd2bin(hour);
	day = bcd2bin(day);
	mon = bcd2bin(mon);
	year = bcd2bin(year);
	y2k = bcd2bin(y2k);

	year += (y2k * 100);

	return mktime64(year, mon, day, hour, min, sec);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int tm_year; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct intersil_dt {int year; int /*<<< orphan*/  weekday; int /*<<< orphan*/  day; scalar_t__ month; scalar_t__ second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; scalar_t__ csec; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_reg; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  START_VAL ; 
 int /*<<< orphan*/  STOP_VAL ; 
 TYPE_1__* intersil_clock ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

int sun3_hwclk(int set, struct rtc_time *t)
{
	volatile struct intersil_dt *todintersil;
	unsigned long flags;

        todintersil = (struct intersil_dt *) &intersil_clock->counter;

	local_irq_save(flags);

	intersil_clock->cmd_reg = STOP_VAL;

	/* set or read the clock */
	if(set) {
		todintersil->csec = 0;
		todintersil->hour = t->tm_hour;
		todintersil->minute = t->tm_min;
		todintersil->second = t->tm_sec;
		todintersil->month = t->tm_mon + 1;
		todintersil->day = t->tm_mday;
		todintersil->year = (t->tm_year - 68) % 100;
		todintersil->weekday = t->tm_wday;
	} else {
		/* read clock */
		t->tm_sec = todintersil->csec;
		t->tm_hour = todintersil->hour;
		t->tm_min = todintersil->minute;
		t->tm_sec = todintersil->second;
		t->tm_mon = todintersil->month - 1;
		t->tm_mday = todintersil->day;
		t->tm_year = todintersil->year + 68;
		t->tm_wday = todintersil->weekday;
		if (t->tm_year < 70)
			t->tm_year += 100;
	}

	intersil_clock->cmd_reg = START_VAL;

	local_irq_restore(flags);

	return 0;

}
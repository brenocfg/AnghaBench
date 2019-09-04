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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void dvb_frontend_sleep_until(ktime_t *waketime, u32 add_usec)
{
	s32 delta;

	*waketime = ktime_add_us(*waketime, add_usec);
	delta = ktime_us_delta(ktime_get_boottime(), *waketime);
	if (delta > 2500) {
		msleep((delta - 1500) / 1000);
		delta = ktime_us_delta(ktime_get_boottime(), *waketime);
	}
	if (delta > 0)
		udelay(delta);
}
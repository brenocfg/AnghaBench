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
typedef  scalar_t__ u32 ;
struct clock_event_device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  HPET_COUNTER ; 
 scalar_t__ HPET_MIN_CYCLES ; 
 int /*<<< orphan*/  HPET_T0_CMP ; 
 scalar_t__ hpet_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hpet_next_event(unsigned long delta,
		struct clock_event_device *evt)
{
	u32 cnt;
	s32 res;

	cnt = hpet_read(HPET_COUNTER);
	cnt += (u32) delta;
	hpet_write(HPET_T0_CMP, cnt);

	res = (s32)(cnt - hpet_read(HPET_COUNTER));

	return res < HPET_MIN_CYCLES ? -ETIME : 0;
}
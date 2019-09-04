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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  clock_comparator; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  enabled_wait () ; 
 scalar_t__ get_tod_clock_fast () ; 
 scalar_t__ local_tick_disable () ; 
 int /*<<< orphan*/  local_tick_enable (scalar_t__) ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 
 scalar_t__ tod_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __udelay_enabled(unsigned long long usecs)
{
	u64 clock_saved, end;

	end = get_tod_clock_fast() + (usecs << 12);
	do {
		clock_saved = 0;
		if (tod_after(S390_lowcore.clock_comparator, end)) {
			clock_saved = local_tick_disable();
			set_clock_comparator(end);
		}
		enabled_wait();
		if (clock_saved)
			local_tick_enable(clock_saved);
	} while (get_tod_clock_fast() < end);
}
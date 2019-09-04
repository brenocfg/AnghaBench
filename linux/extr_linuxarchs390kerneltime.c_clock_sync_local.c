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
struct TYPE_2__ {scalar_t__ clock_comparator; unsigned long long last_update_clock; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 scalar_t__ clock_comparator_max ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 

__attribute__((used)) static void clock_sync_local(unsigned long long delta)
{
	/* Add the delta to the clock comparator. */
	if (S390_lowcore.clock_comparator != clock_comparator_max) {
		S390_lowcore.clock_comparator += delta;
		set_clock_comparator(S390_lowcore.clock_comparator);
	}
	/* Adjust the last_update_clock time-stamp. */
	S390_lowcore.last_update_clock += delta;
}
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
struct kvm_kpit_state {scalar_t__ period; int /*<<< orphan*/  timer; } ;
struct kvm_pit {struct kvm_kpit_state pit_state; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_get_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 __kpit_elapsed(struct kvm_pit *pit)
{
	s64 elapsed;
	ktime_t remaining;
	struct kvm_kpit_state *ps = &pit->pit_state;

	if (!ps->period)
		return 0;

	/*
	 * The Counter does not stop when it reaches zero. In
	 * Modes 0, 1, 4, and 5 the Counter ``wraps around'' to
	 * the highest count, either FFFF hex for binary counting
	 * or 9999 for BCD counting, and continues counting.
	 * Modes 2 and 3 are periodic; the Counter reloads
	 * itself with the initial count and continues counting
	 * from there.
	 */
	remaining = hrtimer_get_remaining(&ps->timer);
	elapsed = ps->period - ktime_to_ns(remaining);

	return elapsed;
}
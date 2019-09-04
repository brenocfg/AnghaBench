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
struct sh_tmu_channel {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct sh_tmu_channel* ced_to_sh_tmu (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  sh_tmu_set_next (struct sh_tmu_channel*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_tmu_clock_event_next(unsigned long delta,
				   struct clock_event_device *ced)
{
	struct sh_tmu_channel *ch = ced_to_sh_tmu(ced);

	BUG_ON(!clockevent_state_oneshot(ced));

	/* program new delta value */
	sh_tmu_set_next(ch, delta, 0);
	return 0;
}
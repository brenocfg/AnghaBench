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
struct mips_perf_event {int cntr_mask; int event_id; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int mipspmu_perf_event_encode(const struct mips_perf_event *pev)
{
/*
 * Top 8 bits for range, next 16 bits for cntr_mask, lowest 8 bits for
 * event_id.
 */
#ifdef CONFIG_MIPS_MT_SMP
	if (num_possible_cpus() > 1)
		return ((unsigned int)pev->range << 24) |
			(pev->cntr_mask & 0xffff00) |
			(pev->event_id & 0xff);
	else
#endif /* CONFIG_MIPS_MT_SMP */
		return ((pev->cntr_mask & 0xffff00) |
			(pev->event_id & 0xff));
}
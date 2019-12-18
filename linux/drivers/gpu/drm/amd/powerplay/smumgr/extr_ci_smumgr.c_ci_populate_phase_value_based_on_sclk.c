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
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {int dummy; } ;
struct phm_phase_shedding_limits_table {unsigned int count; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ Sclk; } ;

/* Variables and functions */

__attribute__((used)) static void ci_populate_phase_value_based_on_sclk(struct pp_hwmgr *hwmgr,
				const struct phm_phase_shedding_limits_table *pl,
					uint32_t sclk, uint32_t *p_shed)
{
	unsigned int i;

	/* use the minimum phase shedding */
	*p_shed = 1;

	for (i = 0; i < pl->count; i++) {
		if (sclk < pl->entries[i].Sclk) {
			*p_shed = i;
			break;
		}
	}
}
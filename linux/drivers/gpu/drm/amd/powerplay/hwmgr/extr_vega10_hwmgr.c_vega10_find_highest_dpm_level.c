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
typedef  int uint32_t ;
struct vega10_single_dpm_table {scalar_t__ count; TYPE_1__* dpm_levels; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ MAX_REGULAR_DPM_NUMBER ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static uint32_t vega10_find_highest_dpm_level(
		struct vega10_single_dpm_table *table)
{
	uint32_t i = 0;

	if (table->count <= MAX_REGULAR_DPM_NUMBER) {
		for (i = table->count; i > 0; i--) {
			if (table->dpm_levels[i - 1].enabled)
				return i - 1;
		}
	} else {
		pr_info("DPM Table Has Too Many Entries!");
		return MAX_REGULAR_DPM_NUMBER - 1;
	}

	return i;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_3__* clocks_table; } ;
struct smu_context {TYPE_1__ smu_table; } ;
struct TYPE_6__ {TYPE_2__* FClocks; } ;
struct TYPE_5__ {int /*<<< orphan*/  Freq; } ;
typedef  TYPE_3__ DpmClocks_t ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_FCLK_DPM_LEVELS ; 

__attribute__((used)) static int renoir_get_dpm_uclk_limited(struct smu_context *smu, uint32_t *clock, bool max)
{

	DpmClocks_t *table = smu->smu_table.clocks_table;

	if (!clock || !table)
		return -EINVAL;

	if (max)
		*clock = table->FClocks[NUM_FCLK_DPM_LEVELS-1].Freq;
	else
		*clock = table->FClocks[0].Freq;

	return 0;

}
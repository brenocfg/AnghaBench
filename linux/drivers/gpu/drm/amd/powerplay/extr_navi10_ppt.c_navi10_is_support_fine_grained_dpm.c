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
typedef  size_t uint32_t ;
struct TYPE_4__ {TYPE_2__* driver_pptable; } ;
struct smu_context {TYPE_1__ smu_table; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_6__ {scalar_t__ SnapToDiscrete; } ;
struct TYPE_5__ {TYPE_3__* DpmDescriptor; } ;
typedef  TYPE_2__ PPTable_t ;
typedef  TYPE_3__ DpmDescriptor_t ;

/* Variables and functions */
 size_t smu_clk_get_index (struct smu_context*,int) ; 

__attribute__((used)) static bool navi10_is_support_fine_grained_dpm(struct smu_context *smu, enum smu_clk_type clk_type)
{
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	DpmDescriptor_t *dpm_desc = NULL;
	uint32_t clk_index = 0;

	clk_index = smu_clk_get_index(smu, clk_type);
	dpm_desc = &pptable->DpmDescriptor[clk_index];

	/* 0 - Fine grained DPM, 1 - Discrete DPM */
	return dpm_desc->SnapToDiscrete == 0 ? true : false;
}
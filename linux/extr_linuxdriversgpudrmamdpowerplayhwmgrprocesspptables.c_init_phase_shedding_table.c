#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct phm_phase_shedding_limits_table* vddc_phase_shed_limits_table; } ;
struct pp_hwmgr {TYPE_3__ dyn_state; } ;
struct phm_phase_shedding_limits_table {unsigned long count; TYPE_1__* entries; } ;
struct TYPE_13__ {scalar_t__ usTableSize; } ;
struct TYPE_12__ {scalar_t__ usVddcPhaseShedLimitsTableOffset; } ;
struct TYPE_11__ {int ucNumEntries; TYPE_2__* entries; } ;
struct TYPE_9__ {scalar_t__ usVoltage; scalar_t__ usSclkLow; scalar_t__ usMclkLow; scalar_t__ ucMclkHigh; scalar_t__ ucSclkHigh; } ;
struct TYPE_8__ {unsigned long Voltage; unsigned long Sclk; unsigned long Mclk; } ;
typedef  TYPE_4__ ATOM_PPLIB_PhaseSheddingLimits_Table ;
typedef  TYPE_5__ ATOM_PPLIB_POWERPLAYTABLE4 ;
typedef  TYPE_6__ ATOM_PPLIB_POWERPLAYTABLE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct phm_phase_shedding_limits_table* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int init_phase_shedding_table(struct pp_hwmgr *hwmgr,
		const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	if (le16_to_cpu(powerplay_table->usTableSize) >=
	    sizeof(ATOM_PPLIB_POWERPLAYTABLE4)) {
		const ATOM_PPLIB_POWERPLAYTABLE4 *powerplay_table4 =
				(const ATOM_PPLIB_POWERPLAYTABLE4 *)powerplay_table;

		if (0 != powerplay_table4->usVddcPhaseShedLimitsTableOffset) {
			const ATOM_PPLIB_PhaseSheddingLimits_Table *ptable =
				(ATOM_PPLIB_PhaseSheddingLimits_Table *)
				(((unsigned long)powerplay_table4) +
				le16_to_cpu(powerplay_table4->usVddcPhaseShedLimitsTableOffset));
			struct phm_phase_shedding_limits_table *table;
			unsigned long size, i;


			size = sizeof(unsigned long) +
				(sizeof(struct phm_phase_shedding_limits_table) *
				ptable->ucNumEntries);

			table = kzalloc(size, GFP_KERNEL);

			if (table == NULL)
				return -ENOMEM;

			table->count = (unsigned long)ptable->ucNumEntries;

			for (i = 0; i < table->count; i++) {
				table->entries[i].Voltage = (unsigned long)le16_to_cpu(ptable->entries[i].usVoltage);
				table->entries[i].Sclk    = ((unsigned long)ptable->entries[i].ucSclkHigh << 16)
							| le16_to_cpu(ptable->entries[i].usSclkLow);
				table->entries[i].Mclk    = ((unsigned long)ptable->entries[i].ucMclkHigh << 16)
							| le16_to_cpu(ptable->entries[i].usMclkLow);
			}
			hwmgr->dyn_state.vddc_phase_shed_limits_table = table;
		}
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const uchar ;
struct TYPE_3__ {scalar_t__* sdtr_period_tbl; scalar_t__ min_sdtr_index; scalar_t__ max_sdtr_index; } ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */

__attribute__((used)) static uchar AscGetSynPeriodIndex(ASC_DVC_VAR *asc_dvc, uchar syn_time)
{
	const uchar *period_table;
	int max_index;
	int min_index;
	int i;

	period_table = asc_dvc->sdtr_period_tbl;
	max_index = (int)asc_dvc->max_sdtr_index;
	min_index = (int)asc_dvc->min_sdtr_index;
	if ((syn_time <= period_table[max_index])) {
		for (i = min_index; i < (max_index - 1); i++) {
			if (syn_time <= period_table[i]) {
				return (uchar)i;
			}
		}
		return (uchar)max_index;
	} else {
		return (uchar)(max_index + 1);
	}
}
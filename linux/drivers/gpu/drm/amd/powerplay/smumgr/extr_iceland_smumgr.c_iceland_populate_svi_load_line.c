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
struct pp_hwmgr {scalar_t__ smu_backend; } ;
struct TYPE_2__ {int SviLoadLineTrimVddC; scalar_t__ SviLoadLineOffsetVddC; int /*<<< orphan*/  SviLoadLineVddC; int /*<<< orphan*/  SviLoadLineEn; } ;
struct iceland_smumgr {TYPE_1__ power_tune_table; struct iceland_pt_defaults* power_tune_defaults; } ;
struct iceland_pt_defaults {int /*<<< orphan*/  svi_load_line_vddc; int /*<<< orphan*/  svi_load_line_en; } ;

/* Variables and functions */

__attribute__((used)) static int iceland_populate_svi_load_line(struct pp_hwmgr *hwmgr)
{
	struct iceland_smumgr *smu_data = (struct iceland_smumgr *)(hwmgr->smu_backend);
	const struct iceland_pt_defaults *defaults = smu_data->power_tune_defaults;

	smu_data->power_tune_table.SviLoadLineEn = defaults->svi_load_line_en;
	smu_data->power_tune_table.SviLoadLineVddC = defaults->svi_load_line_vddc;
	smu_data->power_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->power_tune_table.SviLoadLineOffsetVddC = 0;

	return 0;
}
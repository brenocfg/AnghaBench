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
struct fiji_smumgr {TYPE_1__ power_tune_table; struct fiji_pt_defaults* power_tune_defaults; } ;
struct fiji_pt_defaults {int /*<<< orphan*/  SviLoadLineVddC; int /*<<< orphan*/  SviLoadLineEn; } ;

/* Variables and functions */

__attribute__((used)) static int fiji_populate_svi_load_line(struct pp_hwmgr *hwmgr)
{
	struct fiji_smumgr *smu_data = (struct fiji_smumgr *)(hwmgr->smu_backend);
	const struct fiji_pt_defaults *defaults = smu_data->power_tune_defaults;

	smu_data->power_tune_table.SviLoadLineEn = defaults->SviLoadLineEn;
	smu_data->power_tune_table.SviLoadLineVddC = defaults->SviLoadLineVddC;
	smu_data->power_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->power_tune_table.SviLoadLineOffsetVddC = 0;

	return 0;
}
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
struct TYPE_2__ {int SviLoadLineTrimVddC; scalar_t__ SviLoadLineOffsetVddC; int /*<<< orphan*/  SviLoadLineVddC; int /*<<< orphan*/  SviLoadLineEn; } ;
struct tonga_smumgr {TYPE_1__ power_tune_table; struct tonga_pt_defaults* power_tune_defaults; } ;
struct tonga_pt_defaults {int /*<<< orphan*/  svi_load_line_vddC; int /*<<< orphan*/  svi_load_line_en; } ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;

/* Variables and functions */

__attribute__((used)) static int tonga_populate_svi_load_line(struct pp_hwmgr *hwmgr)
{
	struct tonga_smumgr *smu_data =
				(struct tonga_smumgr *)(hwmgr->smu_backend);
	const struct tonga_pt_defaults *defaults = smu_data->power_tune_defaults;

	smu_data->power_tune_table.SviLoadLineEn = defaults->svi_load_line_en;
	smu_data->power_tune_table.SviLoadLineVddC = defaults->svi_load_line_vddC;
	smu_data->power_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->power_tune_table.SviLoadLineOffsetVddC = 0;

	return 0;
}
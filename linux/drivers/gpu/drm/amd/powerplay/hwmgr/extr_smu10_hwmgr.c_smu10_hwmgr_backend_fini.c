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
struct smu10_clock_voltage_information {int /*<<< orphan*/ * vdd_dep_on_phyclk; int /*<<< orphan*/ * vdd_dep_on_dppclk; int /*<<< orphan*/ * vdd_dep_on_dispclk; int /*<<< orphan*/ * vdd_dep_on_fclk; int /*<<< orphan*/ * vdd_dep_on_socclk; int /*<<< orphan*/ * vdd_dep_on_dcefclk; } ;
struct smu10_hwmgr {struct smu10_clock_voltage_information clock_vol_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vddc_dep_on_dal_pwrl; } ;
struct pp_hwmgr {int /*<<< orphan*/ * backend; TYPE_1__ dyn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu10_hwmgr_backend_fini(struct pp_hwmgr *hwmgr)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);
	struct smu10_clock_voltage_information *pinfo = &(smu10_data->clock_vol_info);

	kfree(pinfo->vdd_dep_on_dcefclk);
	pinfo->vdd_dep_on_dcefclk = NULL;
	kfree(pinfo->vdd_dep_on_socclk);
	pinfo->vdd_dep_on_socclk = NULL;
	kfree(pinfo->vdd_dep_on_fclk);
	pinfo->vdd_dep_on_fclk = NULL;
	kfree(pinfo->vdd_dep_on_dispclk);
	pinfo->vdd_dep_on_dispclk = NULL;
	kfree(pinfo->vdd_dep_on_dppclk);
	pinfo->vdd_dep_on_dppclk = NULL;
	kfree(pinfo->vdd_dep_on_phyclk);
	pinfo->vdd_dep_on_phyclk = NULL;

	kfree(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = NULL;

	kfree(hwmgr->backend);
	hwmgr->backend = NULL;

	return 0;
}
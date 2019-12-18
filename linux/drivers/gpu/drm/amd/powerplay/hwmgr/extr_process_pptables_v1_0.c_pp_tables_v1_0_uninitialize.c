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
struct TYPE_2__ {int /*<<< orphan*/ * cac_dtp_table; } ;
struct pp_hwmgr {int /*<<< orphan*/ * pptable; TYPE_1__ dyn_state; } ;
struct phm_ppt_v1_information {int /*<<< orphan*/ * gpio_table; int /*<<< orphan*/ * pcie_table; int /*<<< orphan*/ * ppm_parameter_table; int /*<<< orphan*/ * cac_dtp_table; int /*<<< orphan*/ * mm_dep_table; int /*<<< orphan*/ * vddgfx_lookup_table; int /*<<< orphan*/ * vddc_lookup_table; int /*<<< orphan*/ * valid_sclk_values; int /*<<< orphan*/ * valid_mclk_values; int /*<<< orphan*/ * vdd_dep_on_mclk; int /*<<< orphan*/ * vdd_dep_on_sclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_tables_v1_0_uninitialize(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v1_information *pp_table_information =
		(struct phm_ppt_v1_information *)(hwmgr->pptable);

	kfree(pp_table_information->vdd_dep_on_sclk);
	pp_table_information->vdd_dep_on_sclk = NULL;

	kfree(pp_table_information->vdd_dep_on_mclk);
	pp_table_information->vdd_dep_on_mclk = NULL;

	kfree(pp_table_information->valid_mclk_values);
	pp_table_information->valid_mclk_values = NULL;

	kfree(pp_table_information->valid_sclk_values);
	pp_table_information->valid_sclk_values = NULL;

	kfree(pp_table_information->vddc_lookup_table);
	pp_table_information->vddc_lookup_table = NULL;

	kfree(pp_table_information->vddgfx_lookup_table);
	pp_table_information->vddgfx_lookup_table = NULL;

	kfree(pp_table_information->mm_dep_table);
	pp_table_information->mm_dep_table = NULL;

	kfree(pp_table_information->cac_dtp_table);
	pp_table_information->cac_dtp_table = NULL;

	kfree(hwmgr->dyn_state.cac_dtp_table);
	hwmgr->dyn_state.cac_dtp_table = NULL;

	kfree(pp_table_information->ppm_parameter_table);
	pp_table_information->ppm_parameter_table = NULL;

	kfree(pp_table_information->pcie_table);
	pp_table_information->pcie_table = NULL;

	kfree(pp_table_information->gpio_table);
	pp_table_information->gpio_table = NULL;

	kfree(hwmgr->pptable);
	hwmgr->pptable = NULL;

	return 0;
}
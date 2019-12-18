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
struct vega20_single_dpm_table {int count; int /*<<< orphan*/  dpm_state; TYPE_1__* dpm_levels; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table fclk_table; struct vega20_single_dpm_table phy_table; struct vega20_single_dpm_table display_table; struct vega20_single_dpm_table pixel_table; struct vega20_single_dpm_table dcef_table; struct vega20_single_dpm_table dclk_table; struct vega20_single_dpm_table vclk_table; struct vega20_single_dpm_table eclk_table; struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; struct vega20_single_dpm_table soc_table; } ;
struct smu_dpm_context {int /*<<< orphan*/  golden_dpm_context; struct vega20_dpm_table* dpm_context; } ;
struct TYPE_5__ {int socclk; int gfxclk; int uclk; int eclk; int vclk; int dclk; int dcefclk; } ;
struct TYPE_6__ {TYPE_2__ boot_values; } ;
struct smu_context {TYPE_3__ smu_table; struct smu_dpm_context smu_dpm; } ;
struct TYPE_4__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_DPM_FCLK_BIT ; 
 int /*<<< orphan*/  PPCLK_DCEFCLK ; 
 int /*<<< orphan*/  PPCLK_DCLK ; 
 int /*<<< orphan*/  PPCLK_DISPCLK ; 
 int /*<<< orphan*/  PPCLK_ECLK ; 
 int /*<<< orphan*/  PPCLK_FCLK ; 
 int /*<<< orphan*/  PPCLK_GFXCLK ; 
 int /*<<< orphan*/  PPCLK_PHYCLK ; 
 int /*<<< orphan*/  PPCLK_PIXCLK ; 
 int /*<<< orphan*/  PPCLK_SOCCLK ; 
 int /*<<< orphan*/  PPCLK_UCLK ; 
 int /*<<< orphan*/  PPCLK_VCLK ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_DCEFCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_GFXCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_SOCCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UVD_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_VCE_BIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct vega20_dpm_table*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega20_init_single_dpm_state (int /*<<< orphan*/ *) ; 
 int vega20_set_single_dpm_table (struct smu_context*,struct vega20_single_dpm_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_set_default_dpm_table(struct smu_context *smu)
{
	int ret;

	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	struct vega20_dpm_table *dpm_table = NULL;
	struct vega20_single_dpm_table *single_dpm_table;

	dpm_table = smu_dpm->dpm_context;

	/* socclk */
	single_dpm_table = &(dpm_table->soc_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_SOCCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get socclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.socclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* gfxclk */
	single_dpm_table = &(dpm_table->gfx_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_GFXCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get gfxclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.gfxclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* memclk */
	single_dpm_table = &(dpm_table->mem_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_UCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get memclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.uclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* eclk */
	single_dpm_table = &(dpm_table->eclk_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_VCE_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table, PPCLK_ECLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get eclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.eclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* vclk */
	single_dpm_table = &(dpm_table->vclk_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UVD_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table, PPCLK_VCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get vclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.vclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* dclk */
	single_dpm_table = &(dpm_table->dclk_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UVD_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table, PPCLK_DCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get dclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* dcefclk */
	single_dpm_table = &(dpm_table->dcef_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_DCEFCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get dcefclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 1;
		single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dcefclk / 100;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* pixclk */
	single_dpm_table = &(dpm_table->pixel_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_PIXCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get pixclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 0;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* dispclk */
	single_dpm_table = &(dpm_table->display_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_DISPCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get dispclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 0;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* phyclk */
	single_dpm_table = &(dpm_table->phy_table);

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_PHYCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get phyclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 0;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	/* fclk */
	single_dpm_table = &(dpm_table->fclk_table);

	if (smu_feature_is_enabled(smu,FEATURE_DPM_FCLK_BIT)) {
		ret = vega20_set_single_dpm_table(smu, single_dpm_table,
						  PPCLK_FCLK);
		if (ret) {
			pr_err("[SetupDefaultDpmTable] failed to get fclk dpm levels!");
			return ret;
		}
	} else {
		single_dpm_table->count = 0;
	}
	vega20_init_single_dpm_state(&(single_dpm_table->dpm_state));

	memcpy(smu_dpm->golden_dpm_context, dpm_table,
	       sizeof(struct vega20_dpm_table));

	return 0;
}
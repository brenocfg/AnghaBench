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
struct vega10_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  smu_feature_bitmap; scalar_t__ supported; } ;

/* Variables and functions */
 size_t GNLD_ACG ; 
 int /*<<< orphan*/  vega10_enable_smc_features (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_acg_disable(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->smu_features[GNLD_ACG].supported && 
	    data->smu_features[GNLD_ACG].enabled)
		if (!vega10_enable_smc_features(hwmgr, false,
			data->smu_features[GNLD_ACG].smu_feature_bitmap))
			data->smu_features[GNLD_ACG].enabled = false;

	return 0;
}
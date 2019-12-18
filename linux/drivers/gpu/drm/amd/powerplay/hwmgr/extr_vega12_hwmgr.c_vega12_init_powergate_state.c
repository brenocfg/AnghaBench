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
struct vega12_hwmgr {int uvd_power_gated; int vce_power_gated; TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t GNLD_DPM_UVD ; 
 size_t GNLD_DPM_VCE ; 

__attribute__((used)) static void vega12_init_powergate_state(struct pp_hwmgr *hwmgr)
{
	struct vega12_hwmgr *data =
			(struct vega12_hwmgr *)(hwmgr->backend);

	data->uvd_power_gated = true;
	data->vce_power_gated = true;

	if (data->smu_features[GNLD_DPM_UVD].enabled)
		data->uvd_power_gated = false;

	if (data->smu_features[GNLD_DPM_VCE].enabled)
		data->vce_power_gated = false;
}
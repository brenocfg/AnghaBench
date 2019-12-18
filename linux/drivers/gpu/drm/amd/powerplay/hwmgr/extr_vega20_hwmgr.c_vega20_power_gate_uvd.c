#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vega20_hwmgr {int uvd_power_gated; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  vega20_enable_disable_uvd_dpm (struct pp_hwmgr*,int) ; 

__attribute__((used)) static void vega20_power_gate_uvd(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);

	if (data->uvd_power_gated == bgate)
		return ;

	data->uvd_power_gated = bgate;
	vega20_enable_disable_uvd_dpm(hwmgr, !bgate);
}
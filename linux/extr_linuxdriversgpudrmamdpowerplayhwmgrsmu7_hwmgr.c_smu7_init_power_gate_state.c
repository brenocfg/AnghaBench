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
struct smu7_hwmgr {int uvd_power_gated; int vce_power_gated; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */

__attribute__((used)) static int smu7_init_power_gate_state(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	data->uvd_power_gated = false;
	data->vce_power_gated = false;

	return 0;
}
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
struct smu8_hwmgr {int uvd_power_gated; int vce_power_gated; int samu_power_gated; int acp_power_gated; int pgacpinit; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static void smu8_init_power_gate_state(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->uvd_power_gated = false;
	data->vce_power_gated = false;
	data->samu_power_gated = false;
	data->acp_power_gated = false;
	data->pgacpinit = true;
}
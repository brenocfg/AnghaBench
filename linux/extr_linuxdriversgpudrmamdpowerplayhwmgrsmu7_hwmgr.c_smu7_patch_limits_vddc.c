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
typedef  void* uint32_t ;
struct smu7_hwmgr {int /*<<< orphan*/  vddci_leakage; int /*<<< orphan*/  vddc_leakage; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct phm_clock_and_voltage_limits {void* vddci; void* vddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_patch_ppt_v0_with_vdd_leakage (struct pp_hwmgr*,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu7_patch_limits_vddc(struct pp_hwmgr *hwmgr,
				  struct phm_clock_and_voltage_limits *tab)
{
	uint32_t vddc, vddci;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (tab) {
		vddc = tab->vddc;
		smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &vddc,
						   &data->vddc_leakage);
		tab->vddc = vddc;
		vddci = tab->vddci;
		smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &vddci,
						   &data->vddci_leakage);
		tab->vddci = vddci;
	}

	return 0;
}
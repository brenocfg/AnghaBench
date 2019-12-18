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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct pp_hwmgr {scalar_t__ chip_id; struct amdgpu_device* adev; scalar_t__ pptable; } ;
struct phm_ppt_v1_voltage_lookup_table {int count; TYPE_2__* entries; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_voltage_lookup_table* vddc_lookup_table; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {int count; TYPE_3__* entries; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_6__ {size_t vddInd; } ;
struct TYPE_5__ {int us_vdd; } ;
struct TYPE_4__ {int revision; int subsystem_device; int subsystem_vendor; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS10 ; 

__attribute__((used)) static int smu7_patch_voltage_workaround(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v1_information *table_info =
		       (struct phm_ppt_v1_information *)(hwmgr->pptable);
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_mclk_table;
	struct phm_ppt_v1_voltage_lookup_table *lookup_table;
	uint32_t i;
	uint32_t hw_revision, sub_vendor_id, sub_sys_id;
	struct amdgpu_device *adev = hwmgr->adev;

	if (table_info != NULL) {
		dep_mclk_table = table_info->vdd_dep_on_mclk;
		lookup_table = table_info->vddc_lookup_table;
	} else
		return 0;

	hw_revision = adev->pdev->revision;
	sub_sys_id = adev->pdev->subsystem_device;
	sub_vendor_id = adev->pdev->subsystem_vendor;

	if (hwmgr->chip_id == CHIP_POLARIS10 && hw_revision == 0xC7 &&
			((sub_sys_id == 0xb37 && sub_vendor_id == 0x1002) ||
		    (sub_sys_id == 0x4a8 && sub_vendor_id == 0x1043) ||
		    (sub_sys_id == 0x9480 && sub_vendor_id == 0x1682))) {
		if (lookup_table->entries[dep_mclk_table->entries[dep_mclk_table->count-1].vddInd].us_vdd >= 1000)
			return 0;

		for (i = 0; i < lookup_table->count; i++) {
			if (lookup_table->entries[i].us_vdd < 0xff01 && lookup_table->entries[i].us_vdd >= 1000) {
				dep_mclk_table->entries[dep_mclk_table->count-1].vddInd = (uint8_t) i;
				return 0;
			}
		}
	}
	return 0;
}
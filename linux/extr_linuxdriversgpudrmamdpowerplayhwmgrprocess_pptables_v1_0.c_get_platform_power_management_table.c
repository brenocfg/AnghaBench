#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {scalar_t__ pptable; } ;
struct phm_ppt_v1_information {struct phm_ppm_table* ppm_parameter_table; } ;
struct phm_ppm_table {int /*<<< orphan*/  tj_max; int /*<<< orphan*/  dgpu_ulv_power; int /*<<< orphan*/  dgpu_tdp; int /*<<< orphan*/  apu_tdp; int /*<<< orphan*/  small_ac_platform_tdc; int /*<<< orphan*/  platform_tdc; int /*<<< orphan*/  small_ac_platform_tdp; int /*<<< orphan*/  platform_tdp; int /*<<< orphan*/  cpu_core_number; int /*<<< orphan*/  ppm_design; } ;
struct TYPE_3__ {int /*<<< orphan*/  ulTjmax; int /*<<< orphan*/  ulDGpuUlvPower; int /*<<< orphan*/  ulDGpuTDP; int /*<<< orphan*/  ulApuTDP; int /*<<< orphan*/  ulSmallACPlatformTDC; int /*<<< orphan*/  ulPlatformTDC; int /*<<< orphan*/  ulSmallACPlatformTDP; int /*<<< orphan*/  ulPlatformTDP; int /*<<< orphan*/  usCpuCoreNumber; int /*<<< orphan*/  ucPpmDesign; } ;
typedef  TYPE_1__ ATOM_Tonga_PPM_Table ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct phm_ppm_table* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_platform_power_management_table(
		struct pp_hwmgr *hwmgr,
		ATOM_Tonga_PPM_Table *atom_ppm_table)
{
	struct phm_ppm_table *ptr = kzalloc(sizeof(ATOM_Tonga_PPM_Table), GFP_KERNEL);
	struct phm_ppt_v1_information *pp_table_information =
		(struct phm_ppt_v1_information *)(hwmgr->pptable);

	if (NULL == ptr)
		return -ENOMEM;

	ptr->ppm_design
		= atom_ppm_table->ucPpmDesign;
	ptr->cpu_core_number
		= atom_ppm_table->usCpuCoreNumber;
	ptr->platform_tdp
		= atom_ppm_table->ulPlatformTDP;
	ptr->small_ac_platform_tdp
		= atom_ppm_table->ulSmallACPlatformTDP;
	ptr->platform_tdc
		= atom_ppm_table->ulPlatformTDC;
	ptr->small_ac_platform_tdc
		= atom_ppm_table->ulSmallACPlatformTDC;
	ptr->apu_tdp
		= atom_ppm_table->ulApuTDP;
	ptr->dgpu_tdp
		= atom_ppm_table->ulDGpuTDP;
	ptr->dgpu_ulv_power
		= atom_ppm_table->ulDGpuUlvPower;
	ptr->tj_max
		= atom_ppm_table->ulTjmax;

	pp_table_information->ppm_parameter_table = ptr;

	return 0;
}
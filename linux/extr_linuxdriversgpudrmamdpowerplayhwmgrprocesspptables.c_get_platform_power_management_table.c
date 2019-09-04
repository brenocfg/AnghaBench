#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct phm_ppm_table* ppm_parameter_table; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
struct phm_ppm_table {void* tj_max; void* dgpu_ulv_power; void* dgpu_tdp; void* apu_tdp; void* small_ac_platform_tdc; void* platform_tdc; void* small_ac_platform_tdp; void* platform_tdp; int /*<<< orphan*/  cpu_core_number; int /*<<< orphan*/  ppm_design; } ;
struct TYPE_5__ {int /*<<< orphan*/  ulTjmax; int /*<<< orphan*/  ulDGpuUlvPower; int /*<<< orphan*/  ulDGpuTDP; int /*<<< orphan*/  ulApuTDP; int /*<<< orphan*/  ulSmallACPlatformTDC; int /*<<< orphan*/  ulPlatformTDC; int /*<<< orphan*/  ulSmallACPlatformTDP; int /*<<< orphan*/  ulPlatformTDP; int /*<<< orphan*/  usCpuCoreNumber; int /*<<< orphan*/  ucPpmDesign; } ;
typedef  TYPE_2__ ATOM_PPLIB_PPM_Table ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct phm_ppm_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_platform_power_management_table(struct pp_hwmgr *hwmgr,
			ATOM_PPLIB_PPM_Table *atom_ppm_table)
{
	struct phm_ppm_table *ptr = kzalloc(sizeof(struct phm_ppm_table), GFP_KERNEL);

	if (NULL == ptr)
		return -ENOMEM;

	ptr->ppm_design            = atom_ppm_table->ucPpmDesign;
	ptr->cpu_core_number        = le16_to_cpu(atom_ppm_table->usCpuCoreNumber);
	ptr->platform_tdp          = le32_to_cpu(atom_ppm_table->ulPlatformTDP);
	ptr->small_ac_platform_tdp   = le32_to_cpu(atom_ppm_table->ulSmallACPlatformTDP);
	ptr->platform_tdc          = le32_to_cpu(atom_ppm_table->ulPlatformTDC);
	ptr->small_ac_platform_tdc   = le32_to_cpu(atom_ppm_table->ulSmallACPlatformTDC);
	ptr->apu_tdp               = le32_to_cpu(atom_ppm_table->ulApuTDP);
	ptr->dgpu_tdp              = le32_to_cpu(atom_ppm_table->ulDGpuTDP);
	ptr->dgpu_ulv_power         = le32_to_cpu(atom_ppm_table->ulDGpuUlvPower);
	ptr->tj_max                = le32_to_cpu(atom_ppm_table->ulTjmax);
	hwmgr->dyn_state.ppm_parameter_table = ptr;

	return 0;
}
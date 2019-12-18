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
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THM ; 
 int THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT ; 
 int THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT ; 
 int THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmTHM_THERMAL_INT_ENA ; 

__attribute__((used)) static int vega20_thermal_enable_alert(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t val = 0;

	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, val);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_dpm_quirk {scalar_t__ chip_device; scalar_t__ chip_vendor; scalar_t__ subsys_vendor; scalar_t__ subsys_device; } ;
struct TYPE_4__ {scalar_t__ pm_method; } ;
struct radeon_device {int family; int flags; TYPE_2__ pm; int /*<<< orphan*/  smc_fw; int /*<<< orphan*/  rlc_fw; TYPE_1__* pdev; } ;
struct TYPE_3__ {scalar_t__ vendor; scalar_t__ device; scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
#define  CHIP_ARUBA 161 
#define  CHIP_BARTS 160 
#define  CHIP_BONAIRE 159 
#define  CHIP_CAICOS 158 
#define  CHIP_CAYMAN 157 
#define  CHIP_CEDAR 156 
#define  CHIP_CYPRESS 155 
#define  CHIP_HAINAN 154 
#define  CHIP_HAWAII 153 
#define  CHIP_HEMLOCK 152 
#define  CHIP_JUNIPER 151 
#define  CHIP_KABINI 150 
#define  CHIP_KAVERI 149 
#define  CHIP_MULLINS 148 
#define  CHIP_OLAND 147 
#define  CHIP_PALM 146 
#define  CHIP_PITCAIRN 145 
#define  CHIP_REDWOOD 144 
#define  CHIP_RS780 143 
#define  CHIP_RS880 142 
#define  CHIP_RV610 141 
#define  CHIP_RV620 140 
#define  CHIP_RV630 139 
#define  CHIP_RV635 138 
#define  CHIP_RV670 137 
#define  CHIP_RV710 136 
#define  CHIP_RV730 135 
#define  CHIP_RV740 134 
#define  CHIP_RV770 133 
#define  CHIP_SUMO 132 
#define  CHIP_SUMO2 131 
#define  CHIP_TAHITI 130 
#define  CHIP_TURKS 129 
#define  CHIP_VERDE 128 
 scalar_t__ PM_METHOD_DPM ; 
 void* PM_METHOD_PROFILE ; 
 int RADEON_IS_IGP ; 
 int radeon_dpm ; 
 struct radeon_dpm_quirk* radeon_dpm_quirk_list ; 
 int radeon_pm_init_dpm (struct radeon_device*) ; 
 int radeon_pm_init_old (struct radeon_device*) ; 

int radeon_pm_init(struct radeon_device *rdev)
{
	struct radeon_dpm_quirk *p = radeon_dpm_quirk_list;
	bool disable_dpm = false;

	/* Apply dpm quirks */
	while (p && p->chip_device != 0) {
		if (rdev->pdev->vendor == p->chip_vendor &&
		    rdev->pdev->device == p->chip_device &&
		    rdev->pdev->subsystem_vendor == p->subsys_vendor &&
		    rdev->pdev->subsystem_device == p->subsys_device) {
			disable_dpm = true;
			break;
		}
		++p;
	}

	/* enable dpm on rv6xx+ */
	switch (rdev->family) {
	case CHIP_RV610:
	case CHIP_RV630:
	case CHIP_RV620:
	case CHIP_RV635:
	case CHIP_RV670:
	case CHIP_RS780:
	case CHIP_RS880:
	case CHIP_RV770:
		/* DPM requires the RLC, RV770+ dGPU requires SMC */
		if (!rdev->rlc_fw)
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else if ((rdev->family >= CHIP_RV770) &&
			 (!(rdev->flags & RADEON_IS_IGP)) &&
			 (!rdev->smc_fw))
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else if (radeon_dpm == 1)
			rdev->pm.pm_method = PM_METHOD_DPM;
		else
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		break;
	case CHIP_RV730:
	case CHIP_RV710:
	case CHIP_RV740:
	case CHIP_CEDAR:
	case CHIP_REDWOOD:
	case CHIP_JUNIPER:
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
	case CHIP_PALM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_BARTS:
	case CHIP_TURKS:
	case CHIP_CAICOS:
	case CHIP_CAYMAN:
	case CHIP_ARUBA:
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
	case CHIP_OLAND:
	case CHIP_HAINAN:
	case CHIP_BONAIRE:
	case CHIP_KABINI:
	case CHIP_KAVERI:
	case CHIP_HAWAII:
	case CHIP_MULLINS:
		/* DPM requires the RLC, RV770+ dGPU requires SMC */
		if (!rdev->rlc_fw)
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else if ((rdev->family >= CHIP_RV770) &&
			 (!(rdev->flags & RADEON_IS_IGP)) &&
			 (!rdev->smc_fw))
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else if (disable_dpm && (radeon_dpm == -1))
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else if (radeon_dpm == 0)
			rdev->pm.pm_method = PM_METHOD_PROFILE;
		else
			rdev->pm.pm_method = PM_METHOD_DPM;
		break;
	default:
		/* default to profile method */
		rdev->pm.pm_method = PM_METHOD_PROFILE;
		break;
	}

	if (rdev->pm.pm_method == PM_METHOD_DPM)
		return radeon_pm_init_dpm(rdev);
	else
		return radeon_pm_init_old(rdev);
}
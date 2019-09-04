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
typedef  int u32 ;
struct radeon_ps {int class; int caps; int class2; } ;
struct TYPE_3__ {int num_ps; struct radeon_ps* uvd_ps; struct radeon_ps* boot_ps; struct radeon_ps* ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
typedef  enum radeon_pm_state_type { ____Placeholder_radeon_pm_state_type } radeon_pm_state_type ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_MVC ; 
 int ATOM_PPLIB_CLASSIFICATION2_ULV ; 
 int ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE ; 
 int ATOM_PPLIB_CLASSIFICATION_ACPI ; 
 int ATOM_PPLIB_CLASSIFICATION_HD2STATE ; 
 int ATOM_PPLIB_CLASSIFICATION_HDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_SDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_THERMAL ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_BALANCED ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_BATTERY ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE ; 
 int ATOM_PPLIB_SINGLE_DISPLAY_ONLY ; 
#define  POWER_STATE_TYPE_BALANCED 140 
#define  POWER_STATE_TYPE_BATTERY 139 
#define  POWER_STATE_TYPE_INTERNAL_3DPERF 138 
#define  POWER_STATE_TYPE_INTERNAL_ACPI 137 
#define  POWER_STATE_TYPE_INTERNAL_BOOT 136 
#define  POWER_STATE_TYPE_INTERNAL_THERMAL 135 
#define  POWER_STATE_TYPE_INTERNAL_ULV 134 
#define  POWER_STATE_TYPE_INTERNAL_UVD 133 
#define  POWER_STATE_TYPE_INTERNAL_UVD_HD 132 
#define  POWER_STATE_TYPE_INTERNAL_UVD_HD2 131 
#define  POWER_STATE_TYPE_INTERNAL_UVD_MVC 130 
#define  POWER_STATE_TYPE_INTERNAL_UVD_SD 129 
#define  POWER_STATE_TYPE_PERFORMANCE 128 
 int radeon_dpm_single_display (struct radeon_device*) ; 

__attribute__((used)) static struct radeon_ps *radeon_dpm_pick_power_state(struct radeon_device *rdev,
						     enum radeon_pm_state_type dpm_state)
{
	int i;
	struct radeon_ps *ps;
	u32 ui_class;
	bool single_display = radeon_dpm_single_display(rdev);

	/* certain older asics have a separare 3D performance state,
	 * so try that first if the user selected performance
	 */
	if (dpm_state == POWER_STATE_TYPE_PERFORMANCE)
		dpm_state = POWER_STATE_TYPE_INTERNAL_3DPERF;
	/* balanced states don't exist at the moment */
	if (dpm_state == POWER_STATE_TYPE_BALANCED)
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;

restart_search:
	/* Pick the best power state based on current conditions */
	for (i = 0; i < rdev->pm.dpm.num_ps; i++) {
		ps = &rdev->pm.dpm.ps[i];
		ui_class = ps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK;
		switch (dpm_state) {
		/* user states */
		case POWER_STATE_TYPE_BATTERY:
			if (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY) {
				if (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) {
					if (single_display)
						return ps;
				} else
					return ps;
			}
			break;
		case POWER_STATE_TYPE_BALANCED:
			if (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BALANCED) {
				if (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) {
					if (single_display)
						return ps;
				} else
					return ps;
			}
			break;
		case POWER_STATE_TYPE_PERFORMANCE:
			if (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) {
				if (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) {
					if (single_display)
						return ps;
				} else
					return ps;
			}
			break;
		/* internal states */
		case POWER_STATE_TYPE_INTERNAL_UVD:
			if (rdev->pm.dpm.uvd_ps)
				return rdev->pm.dpm.uvd_ps;
			else
				break;
		case POWER_STATE_TYPE_INTERNAL_UVD_SD:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_UVD_HD:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_UVD_HD2:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_UVD_MVC:
			if (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_BOOT:
			return rdev->pm.dpm.boot_ps;
		case POWER_STATE_TYPE_INTERNAL_THERMAL:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_ACPI:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_ACPI)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_ULV:
			if (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
				return ps;
			break;
		case POWER_STATE_TYPE_INTERNAL_3DPERF:
			if (ps->class & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
				return ps;
			break;
		default:
			break;
		}
	}
	/* use a fallback state if we didn't match */
	switch (dpm_state) {
	case POWER_STATE_TYPE_INTERNAL_UVD_SD:
		dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
		goto restart_search;
	case POWER_STATE_TYPE_INTERNAL_UVD_HD:
	case POWER_STATE_TYPE_INTERNAL_UVD_HD2:
	case POWER_STATE_TYPE_INTERNAL_UVD_MVC:
		if (rdev->pm.dpm.uvd_ps) {
			return rdev->pm.dpm.uvd_ps;
		} else {
			dpm_state = POWER_STATE_TYPE_PERFORMANCE;
			goto restart_search;
		}
	case POWER_STATE_TYPE_INTERNAL_THERMAL:
		dpm_state = POWER_STATE_TYPE_INTERNAL_ACPI;
		goto restart_search;
	case POWER_STATE_TYPE_INTERNAL_ACPI:
		dpm_state = POWER_STATE_TYPE_BATTERY;
		goto restart_search;
	case POWER_STATE_TYPE_BATTERY:
	case POWER_STATE_TYPE_BALANCED:
	case POWER_STATE_TYPE_INTERNAL_3DPERF:
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;
		goto restart_search;
	default:
		break;
	}

	return NULL;
}
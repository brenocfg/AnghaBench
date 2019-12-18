#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {scalar_t__ family; TYPE_1__* pdev; } ;
struct ci_power_info {int caps_power_containment; int caps_cac; int caps_sq_ramping; int caps_db_ramping; int caps_td_ramping; int caps_tcp_ramping; int enable_bapm_feature; int enable_tdc_limit_feature; int enable_pkg_pwr_tracking_feature; scalar_t__ dte_tj_offset; int /*<<< orphan*/ * powertune_defaults; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 scalar_t__ CHIP_HAWAII ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  defaults_bonaire_xt ; 
 int /*<<< orphan*/  defaults_hawaii_pro ; 
 int /*<<< orphan*/  defaults_hawaii_xt ; 
 int /*<<< orphan*/  defaults_saturn_xt ; 

__attribute__((used)) static void ci_initialize_powertune_defaults(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);

	switch (rdev->pdev->device) {
	case 0x6649:
	case 0x6650:
	case 0x6651:
	case 0x6658:
	case 0x665C:
	case 0x665D:
	default:
		pi->powertune_defaults = &defaults_bonaire_xt;
		break;
	case 0x6640:
	case 0x6641:
	case 0x6646:
	case 0x6647:
		pi->powertune_defaults = &defaults_saturn_xt;
		break;
	case 0x67B8:
	case 0x67B0:
		pi->powertune_defaults = &defaults_hawaii_xt;
		break;
	case 0x67BA:
	case 0x67B1:
		pi->powertune_defaults = &defaults_hawaii_pro;
		break;
	case 0x67A0:
	case 0x67A1:
	case 0x67A2:
	case 0x67A8:
	case 0x67A9:
	case 0x67AA:
	case 0x67B9:
	case 0x67BE:
		pi->powertune_defaults = &defaults_bonaire_xt;
		break;
	}

	pi->dte_tj_offset = 0;

	pi->caps_power_containment = true;
	pi->caps_cac = false;
	pi->caps_sq_ramping = false;
	pi->caps_db_ramping = false;
	pi->caps_td_ramping = false;
	pi->caps_tcp_ramping = false;

	if (pi->caps_power_containment) {
		pi->caps_cac = true;
		if (rdev->family == CHIP_HAWAII)
			pi->enable_bapm_feature = false;
		else
			pi->enable_bapm_feature = true;
		pi->enable_tdc_limit_feature = true;
		pi->enable_pkg_pwr_tracking_feature = true;
	}
}
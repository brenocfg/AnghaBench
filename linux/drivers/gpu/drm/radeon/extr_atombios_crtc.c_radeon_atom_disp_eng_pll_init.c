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
struct TYPE_2__ {int /*<<< orphan*/  default_dispclk; } ;
struct radeon_device {TYPE_1__ clock; } ;
struct radeon_atom_ss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_DCPLL ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_DCPLL ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  atombios_crtc_program_ss (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct radeon_atom_ss*) ; 
 int /*<<< orphan*/  atombios_crtc_set_disp_eng_pll (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_atom_disp_eng_pll_init(struct radeon_device *rdev)
{
	/* always set DCPLL */
	if (ASIC_IS_DCE6(rdev))
		atombios_crtc_set_disp_eng_pll(rdev, rdev->clock.default_dispclk);
	else if (ASIC_IS_DCE4(rdev)) {
		struct radeon_atom_ss ss;
		bool ss_enabled = radeon_atombios_get_asic_ss_info(rdev, &ss,
								   ASIC_INTERNAL_SS_ON_DCPLL,
								   rdev->clock.default_dispclk);
		if (ss_enabled)
			atombios_crtc_program_ss(rdev, ATOM_DISABLE, ATOM_DCPLL, -1, &ss);
		/* XXX: DCE5, make sure voltage, dispclk is high enough */
		atombios_crtc_set_disp_eng_pll(rdev, rdev->clock.default_dispclk);
		if (ss_enabled)
			atombios_crtc_program_ss(rdev, ATOM_ENABLE, ATOM_DCPLL, -1, &ss);
	}

}
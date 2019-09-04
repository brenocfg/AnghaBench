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
typedef  scalar_t__ u32 ;
struct trinity_power_info {scalar_t__ override_dynamic_mgpg; } ;
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {int /*<<< orphan*/  post_div; } ;

/* Variables and functions */
 scalar_t__ ATI_REV_ID_MASK ; 
 scalar_t__ ATI_REV_ID_SHIFT ; 
 int /*<<< orphan*/  CG_GIPOT (scalar_t__) ; 
 int /*<<< orphan*/  CG_GIPOTS ; 
 int /*<<< orphan*/  CG_GIPOT_MASK ; 
 int /*<<< orphan*/  CG_PG_CTRL ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  GFX_POWER_GATING_CNTL ; 
 int /*<<< orphan*/  HW_REV ; 
 scalar_t__ PDS_DIV (int /*<<< orphan*/ ) ; 
 scalar_t__ PDS_DIV_MASK ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SP (scalar_t__) ; 
 scalar_t__ SSSD (int) ; 
 scalar_t__ SSSD_MASK ; 
 int SU (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int,scalar_t__,int,scalar_t__*,scalar_t__*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 scalar_t__ radeon_get_xclk (struct radeon_device*) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_override_dynamic_mg_powergating (struct radeon_device*) ; 

__attribute__((used)) static void trinity_gfx_powergating_initialize(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 p, u;
	u32 value;
	struct atom_clock_dividers dividers;
	u32 xclk = radeon_get_xclk(rdev);
	u32 sssd = 1;
	int ret;
	u32 hw_rev = (RREG32(HW_REV) & ATI_REV_ID_MASK) >> ATI_REV_ID_SHIFT;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     25000, false, &dividers);
	if (ret)
		return;

	value = RREG32_SMC(GFX_POWER_GATING_CNTL);
	value &= ~(SSSD_MASK | PDS_DIV_MASK);
	if (sssd)
		value |= SSSD(1);
	value |= PDS_DIV(dividers.post_div);
	WREG32_SMC(GFX_POWER_GATING_CNTL, value);

	r600_calculate_u_and_p(500, xclk, 16, &p, &u);

	WREG32(CG_PG_CTRL, SP(p) | SU(u));

	WREG32_P(CG_GIPOTS, CG_GIPOT(p), ~CG_GIPOT_MASK);

	/* XXX double check hw_rev */
	if (pi->override_dynamic_mgpg && (hw_rev == 0))
		trinity_override_dynamic_mg_powergating(rdev);

}
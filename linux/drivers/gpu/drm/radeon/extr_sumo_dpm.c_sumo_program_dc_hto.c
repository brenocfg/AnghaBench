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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_4 ; 
 int DC_HDC (int) ; 
 int DC_HDC_MASK ; 
 int DC_HU (int) ; 
 int DC_HU_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int,int,int,int*,int*) ; 
 int radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static void sumo_program_dc_hto(struct radeon_device *rdev)
{
	u32 cg_sclk_dpm_ctrl_4 = RREG32(CG_SCLK_DPM_CTRL_4);
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(100000,
			       xclk, 14, &p, &u);

	cg_sclk_dpm_ctrl_4 &= ~(DC_HDC_MASK | DC_HU_MASK);
	cg_sclk_dpm_ctrl_4 |= DC_HDC(p) | DC_HU(u);

	WREG32(CG_SCLK_DPM_CTRL_4, cg_sclk_dpm_ctrl_4);
}
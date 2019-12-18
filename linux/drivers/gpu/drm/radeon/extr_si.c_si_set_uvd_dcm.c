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
 int CG_DT (int) ; 
 int CG_DT_MASK ; 
 int CLK_OD (int) ; 
 int CLK_OD_MASK ; 
 int DCM ; 
 int DYN_OR_EN ; 
 int DYN_RR_EN ; 
 int G_DIV_ID (int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_CGC_CTRL ; 
 int /*<<< orphan*/  UVD_CGC_CTRL2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_UVD_CTX (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_set_uvd_dcm(struct radeon_device *rdev,
			   bool sw_mode)
{
	u32 tmp, tmp2;

	tmp = RREG32(UVD_CGC_CTRL);
	tmp &= ~(CLK_OD_MASK | CG_DT_MASK);
	tmp |= DCM | CG_DT(1) | CLK_OD(4);

	if (sw_mode) {
		tmp &= ~0x7ffff800;
		tmp2 = DYN_OR_EN | DYN_RR_EN | G_DIV_ID(7);
	} else {
		tmp |= 0x7ffff800;
		tmp2 = 0;
	}

	WREG32(UVD_CGC_CTRL, tmp);
	WREG32_UVD_CTX(UVD_CGC_CTRL2, tmp2);
}
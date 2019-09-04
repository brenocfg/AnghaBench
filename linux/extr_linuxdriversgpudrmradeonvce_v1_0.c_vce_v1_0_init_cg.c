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
 int CGC_DYN_CLOCK_MODE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  VCE_CLOCK_GATING_B ; 
 int /*<<< orphan*/  VCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  VCE_UENC_REG_CLOCK_GATING ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vce_v1_0_init_cg(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG32(VCE_CLOCK_GATING_A);
	tmp |= CGC_DYN_CLOCK_MODE;
	WREG32(VCE_CLOCK_GATING_A, tmp);

	tmp = RREG32(VCE_CLOCK_GATING_B);
	tmp |= 0x1e;
	tmp &= ~0xe100e1;
	WREG32(VCE_CLOCK_GATING_B, tmp);

	tmp = RREG32(VCE_UENC_CLOCK_GATING);
	tmp &= ~0xff9ff000;
	WREG32(VCE_UENC_CLOCK_GATING, tmp);

	tmp = RREG32(VCE_UENC_REG_CLOCK_GATING);
	tmp &= ~0x3ff;
	WREG32(VCE_UENC_REG_CLOCK_GATING, tmp);
}
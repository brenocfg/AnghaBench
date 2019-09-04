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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int UVD_CGC_CTRL2__DYN_OCLK_RAMP_EN_MASK ; 
 int UVD_CGC_CTRL2__DYN_RCLK_RAMP_EN_MASK ; 
 int UVD_CGC_CTRL2__GATER_DIV_ID__SHIFT ; 
 int UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK ; 
 int UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT ; 
 int UVD_CGC_CTRL__CLK_OFF_DELAY_MASK ; 
 int UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK ; 
 int /*<<< orphan*/  UVD_CGC_GATE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_UVD_CTX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixUVD_CGC_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 

__attribute__((used)) static void uvd_v4_2_set_dcm(struct amdgpu_device *adev,
			     bool sw_mode)
{
	u32 tmp, tmp2;

	WREG32_FIELD(UVD_CGC_GATE, REGS, 0);

	tmp = RREG32(mmUVD_CGC_CTRL);
	tmp &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK | UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);
	tmp |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK |
		(1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT) |
		(4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT);

	if (sw_mode) {
		tmp &= ~0x7ffff800;
		tmp2 = UVD_CGC_CTRL2__DYN_OCLK_RAMP_EN_MASK |
			UVD_CGC_CTRL2__DYN_RCLK_RAMP_EN_MASK |
			(7 << UVD_CGC_CTRL2__GATER_DIV_ID__SHIFT);
	} else {
		tmp |= 0x7ffff800;
		tmp2 = 0;
	}

	WREG32(mmUVD_CGC_CTRL, tmp);
	WREG32_UVD_CTX(ixUVD_CGC_CTRL2, tmp2);
}
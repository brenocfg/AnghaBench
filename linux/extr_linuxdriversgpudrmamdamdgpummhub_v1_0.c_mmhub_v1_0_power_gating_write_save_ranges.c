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
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMHUB ; 
 int /*<<< orphan*/  PCTL0_STCTRL_REGISTER_SAVE_RANGE0 ; 
 int /*<<< orphan*/  PCTL0_STCTRL_REG_SAVE_RANGE0_BASE ; 
 int /*<<< orphan*/  PCTL0_STCTRL_REG_SAVE_RANGE0_LIMIT ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REGISTER_SAVE_RANGE0 ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REGISTER_SAVE_RANGE1 ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REGISTER_SAVE_RANGE2 ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE0_BASE ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE0_LIMIT ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE1_BASE ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE1_LIMIT ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE2_BASE ; 
 int /*<<< orphan*/  PCTL1_STCTRL_REG_SAVE_RANGE2_LIMIT ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STCTRL_REGISTER_SAVE_BASE ; 
 int /*<<< orphan*/  STCTRL_REGISTER_SAVE_LIMIT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmPCTL0_STCTRL_REGISTER_SAVE_RANGE0 ; 
 int /*<<< orphan*/  mmPCTL1_STCTRL_REGISTER_SAVE_RANGE0 ; 
 int /*<<< orphan*/  mmPCTL1_STCTRL_REGISTER_SAVE_RANGE1 ; 
 int /*<<< orphan*/  mmPCTL1_STCTRL_REGISTER_SAVE_RANGE2 ; 

__attribute__((used)) static void mmhub_v1_0_power_gating_write_save_ranges(struct amdgpu_device *adev)
{
	uint32_t tmp = 0;

	/* PCTL0_STCTRL_REGISTER_SAVE_RANGE0 */
	tmp = REG_SET_FIELD(tmp, PCTL0_STCTRL_REGISTER_SAVE_RANGE0,
			STCTRL_REGISTER_SAVE_BASE,
			PCTL0_STCTRL_REG_SAVE_RANGE0_BASE);
	tmp = REG_SET_FIELD(tmp, PCTL0_STCTRL_REGISTER_SAVE_RANGE0,
			STCTRL_REGISTER_SAVE_LIMIT,
			PCTL0_STCTRL_REG_SAVE_RANGE0_LIMIT);
	WREG32_SOC15(MMHUB, 0, mmPCTL0_STCTRL_REGISTER_SAVE_RANGE0, tmp);

	/* PCTL1_STCTRL_REGISTER_SAVE_RANGE0 */
	tmp = 0;
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE0,
			STCTRL_REGISTER_SAVE_BASE,
			PCTL1_STCTRL_REG_SAVE_RANGE0_BASE);
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE0,
			STCTRL_REGISTER_SAVE_LIMIT,
			PCTL1_STCTRL_REG_SAVE_RANGE0_LIMIT);
	WREG32_SOC15(MMHUB, 0, mmPCTL1_STCTRL_REGISTER_SAVE_RANGE0, tmp);

	/* PCTL1_STCTRL_REGISTER_SAVE_RANGE1 */
	tmp = 0;
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE1,
			STCTRL_REGISTER_SAVE_BASE,
			PCTL1_STCTRL_REG_SAVE_RANGE1_BASE);
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE1,
			STCTRL_REGISTER_SAVE_LIMIT,
			PCTL1_STCTRL_REG_SAVE_RANGE1_LIMIT);
	WREG32_SOC15(MMHUB, 0, mmPCTL1_STCTRL_REGISTER_SAVE_RANGE1, tmp);

	/* PCTL1_STCTRL_REGISTER_SAVE_RANGE2 */
	tmp = 0;
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE2,
			STCTRL_REGISTER_SAVE_BASE,
			PCTL1_STCTRL_REG_SAVE_RANGE2_BASE);
	tmp = REG_SET_FIELD(tmp, PCTL1_STCTRL_REGISTER_SAVE_RANGE2,
			STCTRL_REGISTER_SAVE_LIMIT,
			PCTL1_STCTRL_REG_SAVE_RANGE2_LIMIT);
	WREG32_SOC15(MMHUB, 0, mmPCTL1_STCTRL_REGISTER_SAVE_RANGE2, tmp);
}
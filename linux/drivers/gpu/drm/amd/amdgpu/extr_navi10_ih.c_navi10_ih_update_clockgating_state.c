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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_IH_CG ; 
 int /*<<< orphan*/  DBUS_MUX_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  DYN_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  IH_CLK_CTRL ; 
 int /*<<< orphan*/  LIMIT_SMN_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  OSSSYS ; 
 int /*<<< orphan*/  OSSSYS_SHARE_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  REG_CLK_SOFT_OVERRIDE ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmIH_CLK_CTRL ; 

__attribute__((used)) static void navi10_ih_update_clockgating_state(struct amdgpu_device *adev,
					       bool enable)
{
	uint32_t data, def, field_val;

	if (adev->cg_flags & AMD_CG_SUPPORT_IH_CG) {
		def = data = RREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL);
		field_val = enable ? 0 : 1;
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     DBUS_MUX_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     OSSSYS_SHARE_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     LIMIT_SMN_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     DYN_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     REG_CLK_SOFT_OVERRIDE, field_val);
		if (def != data)
			WREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL, data);
	}

	return;
}
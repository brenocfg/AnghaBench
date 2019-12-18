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
typedef  scalar_t__ u64 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_debug_params {size_t reg_idx; scalar_t__ enable; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ CFG_BASE ; 
 int CORESIGHT_UNLOCK ; 
 int EINVAL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__* debug_funnel_regs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int goya_config_funnel(struct hl_device *hdev,
		struct hl_debug_params *params)
{
	u64 base_reg;

	if (params->reg_idx >= ARRAY_SIZE(debug_funnel_regs)) {
		dev_err(hdev->dev, "Invalid register index in FUNNEL\n");
		return -EINVAL;
	}

	base_reg = debug_funnel_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	WREG32(base_reg, params->enable ? 0x33F : 0);

	return 0;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_intf {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTF_LINE_COUNT ; 

__attribute__((used)) static u32 dpu_hw_intf_get_line_count(struct dpu_hw_intf *intf)
{
	struct dpu_hw_blk_reg_map *c;

	if (!intf)
		return 0;

	c = &intf->hw;

	return DPU_REG_READ(c, INTF_LINE_COUNT);
}
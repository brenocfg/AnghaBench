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
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pingpong {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PP_TEAR_CHECK_EN ; 

__attribute__((used)) static int dpu_hw_pp_enable_te(struct dpu_hw_pingpong *pp, bool enable)
{
	struct dpu_hw_blk_reg_map *c;

	if (!pp)
		return -EINVAL;
	c = &pp->hw;

	DPU_REG_WRITE(c, PP_TEAR_CHECK_EN, enable);
	return 0;
}
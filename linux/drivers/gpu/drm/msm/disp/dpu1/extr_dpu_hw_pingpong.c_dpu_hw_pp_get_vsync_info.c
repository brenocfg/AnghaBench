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
struct dpu_hw_pp_vsync_info {int rd_ptr_init_val; int rd_ptr_frame_count; int rd_ptr_line_count; int wr_ptr_line_count; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pingpong {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PP_INT_COUNT_VAL ; 
 int /*<<< orphan*/  PP_LINE_COUNT ; 
 int /*<<< orphan*/  PP_VSYNC_INIT_VAL ; 

__attribute__((used)) static int dpu_hw_pp_get_vsync_info(struct dpu_hw_pingpong *pp,
		struct dpu_hw_pp_vsync_info *info)
{
	struct dpu_hw_blk_reg_map *c;
	u32 val;

	if (!pp || !info)
		return -EINVAL;
	c = &pp->hw;

	val = DPU_REG_READ(c, PP_VSYNC_INIT_VAL);
	info->rd_ptr_init_val = val & 0xffff;

	val = DPU_REG_READ(c, PP_INT_COUNT_VAL);
	info->rd_ptr_frame_count = (val & 0xffff0000) >> 16;
	info->rd_ptr_line_count = val & 0xffff;

	val = DPU_REG_READ(c, PP_LINE_COUNT);
	info->wr_ptr_line_count = val & 0xffff;

	return 0;
}
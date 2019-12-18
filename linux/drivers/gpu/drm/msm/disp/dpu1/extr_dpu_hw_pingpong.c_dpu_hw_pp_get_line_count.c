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
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pingpong {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_INT_COUNT_VAL ; 
 int /*<<< orphan*/  PP_SYNC_CONFIG_HEIGHT ; 
 int /*<<< orphan*/  PP_VSYNC_INIT_VAL ; 

__attribute__((used)) static u32 dpu_hw_pp_get_line_count(struct dpu_hw_pingpong *pp)
{
	struct dpu_hw_blk_reg_map *c = &pp->hw;
	u32 height, init;
	u32 line = 0xFFFF;

	if (!pp)
		return 0;
	c = &pp->hw;

	init = DPU_REG_READ(c, PP_VSYNC_INIT_VAL) & 0xFFFF;
	height = DPU_REG_READ(c, PP_SYNC_CONFIG_HEIGHT) & 0xFFFF;

	if (height < init)
		return line;

	line = DPU_REG_READ(c, PP_INT_COUNT_VAL) & 0xFFFF;

	if (line < init)
		line += (0xFFFF - init);
	else
		line -= init;

	return line;
}
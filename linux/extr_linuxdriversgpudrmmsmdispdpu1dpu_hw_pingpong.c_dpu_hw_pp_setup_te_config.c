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
struct dpu_hw_tear_check {int vsync_count; int sync_cfg_height; int vsync_init_val; int rd_ptr_irq; int start_pos; int sync_threshold_continue; int sync_threshold_start; scalar_t__ hw_vsync_mode; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pingpong {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PP_RD_PTR_IRQ ; 
 int /*<<< orphan*/  PP_START_POS ; 
 int /*<<< orphan*/  PP_SYNC_CONFIG_HEIGHT ; 
 int /*<<< orphan*/  PP_SYNC_CONFIG_VSYNC ; 
 int /*<<< orphan*/  PP_SYNC_THRESH ; 
 int /*<<< orphan*/  PP_SYNC_WRCOUNT ; 
 int /*<<< orphan*/  PP_VSYNC_INIT_VAL ; 

__attribute__((used)) static int dpu_hw_pp_setup_te_config(struct dpu_hw_pingpong *pp,
		struct dpu_hw_tear_check *te)
{
	struct dpu_hw_blk_reg_map *c;
	int cfg;

	if (!pp || !te)
		return -EINVAL;
	c = &pp->hw;

	cfg = BIT(19); /*VSYNC_COUNTER_EN */
	if (te->hw_vsync_mode)
		cfg |= BIT(20);

	cfg |= te->vsync_count;

	DPU_REG_WRITE(c, PP_SYNC_CONFIG_VSYNC, cfg);
	DPU_REG_WRITE(c, PP_SYNC_CONFIG_HEIGHT, te->sync_cfg_height);
	DPU_REG_WRITE(c, PP_VSYNC_INIT_VAL, te->vsync_init_val);
	DPU_REG_WRITE(c, PP_RD_PTR_IRQ, te->rd_ptr_irq);
	DPU_REG_WRITE(c, PP_START_POS, te->start_pos);
	DPU_REG_WRITE(c, PP_SYNC_THRESH,
			((te->sync_threshold_continue << 16) |
			 te->sync_threshold_start));
	DPU_REG_WRITE(c, PP_SYNC_WRCOUNT,
			(te->start_pos + te->sync_threshold_start + 1));

	return 0;
}
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
typedef  scalar_t__ u8 ;
struct dpu_mdss_color {int color_0; int color_1; int color_2; int color_3; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_mixer {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LM_BORDER_COLOR_0 ; 
 int /*<<< orphan*/  LM_BORDER_COLOR_1 ; 

__attribute__((used)) static void dpu_hw_lm_setup_border_color(struct dpu_hw_mixer *ctx,
		struct dpu_mdss_color *color,
		u8 border_en)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;

	if (border_en) {
		DPU_REG_WRITE(c, LM_BORDER_COLOR_0,
			(color->color_0 & 0xFFF) |
			((color->color_1 & 0xFFF) << 0x10));
		DPU_REG_WRITE(c, LM_BORDER_COLOR_1,
			(color->color_2 & 0xFFF) |
			((color->color_3 & 0xFFF) << 0x10));
	}
}
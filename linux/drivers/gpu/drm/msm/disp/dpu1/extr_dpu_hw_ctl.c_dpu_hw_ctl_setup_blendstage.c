#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dpu_hw_stage_cfg {int** multirect_index; int** stage; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_ctl {TYPE_1__* mixer_hw_caps; int /*<<< orphan*/  mixer_count; struct dpu_hw_blk_reg_map hw; } ;
typedef  enum dpu_sspp_multirect_index { ____Placeholder_dpu_sspp_multirect_index } dpu_sspp_multirect_index ;
typedef  enum dpu_lm { ____Placeholder_dpu_lm } dpu_lm ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LAYER (int) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT (int) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT2 (int) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT3 (int) ; 
 int CTL_MIXER_BORDER_OUT ; 
 int /*<<< orphan*/  DPU_MIXER_SOURCESPLIT ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int DPU_SSPP_RECT_1 ; 
 int PIPES_PER_STAGE ; 
#define  SSPP_CURSOR0 141 
#define  SSPP_CURSOR1 140 
#define  SSPP_DMA0 139 
#define  SSPP_DMA1 138 
#define  SSPP_DMA2 137 
#define  SSPP_DMA3 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 
 int _mixer_stages (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_hw_ctl_setup_blendstage(struct dpu_hw_ctl *ctx,
	enum dpu_lm lm, struct dpu_hw_stage_cfg *stage_cfg)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 mixercfg = 0, mixercfg_ext = 0, mix, ext;
	u32 mixercfg_ext2 = 0, mixercfg_ext3 = 0;
	int i, j;
	int stages;
	int pipes_per_stage;

	stages = _mixer_stages(ctx->mixer_hw_caps, ctx->mixer_count, lm);
	if (stages < 0)
		return;

	if (test_bit(DPU_MIXER_SOURCESPLIT,
		&ctx->mixer_hw_caps->features))
		pipes_per_stage = PIPES_PER_STAGE;
	else
		pipes_per_stage = 1;

	mixercfg = CTL_MIXER_BORDER_OUT; /* always set BORDER_OUT */

	if (!stage_cfg)
		goto exit;

	for (i = 0; i <= stages; i++) {
		/* overflow to ext register if 'i + 1 > 7' */
		mix = (i + 1) & 0x7;
		ext = i >= 7;

		for (j = 0 ; j < pipes_per_stage; j++) {
			enum dpu_sspp_multirect_index rect_index =
				stage_cfg->multirect_index[i][j];

			switch (stage_cfg->stage[i][j]) {
			case SSPP_VIG0:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext3 |= ((i + 1) & 0xF) << 0;
				} else {
					mixercfg |= mix << 0;
					mixercfg_ext |= ext << 0;
				}
				break;
			case SSPP_VIG1:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext3 |= ((i + 1) & 0xF) << 4;
				} else {
					mixercfg |= mix << 3;
					mixercfg_ext |= ext << 2;
				}
				break;
			case SSPP_VIG2:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext3 |= ((i + 1) & 0xF) << 8;
				} else {
					mixercfg |= mix << 6;
					mixercfg_ext |= ext << 4;
				}
				break;
			case SSPP_VIG3:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext3 |= ((i + 1) & 0xF) << 12;
				} else {
					mixercfg |= mix << 26;
					mixercfg_ext |= ext << 6;
				}
				break;
			case SSPP_RGB0:
				mixercfg |= mix << 9;
				mixercfg_ext |= ext << 8;
				break;
			case SSPP_RGB1:
				mixercfg |= mix << 12;
				mixercfg_ext |= ext << 10;
				break;
			case SSPP_RGB2:
				mixercfg |= mix << 15;
				mixercfg_ext |= ext << 12;
				break;
			case SSPP_RGB3:
				mixercfg |= mix << 29;
				mixercfg_ext |= ext << 14;
				break;
			case SSPP_DMA0:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext2 |= ((i + 1) & 0xF) << 8;
				} else {
					mixercfg |= mix << 18;
					mixercfg_ext |= ext << 16;
				}
				break;
			case SSPP_DMA1:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext2 |= ((i + 1) & 0xF) << 12;
				} else {
					mixercfg |= mix << 21;
					mixercfg_ext |= ext << 18;
				}
				break;
			case SSPP_DMA2:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext2 |= ((i + 1) & 0xF) << 16;
				} else {
					mix |= (i + 1) & 0xF;
					mixercfg_ext2 |= mix << 0;
				}
				break;
			case SSPP_DMA3:
				if (rect_index == DPU_SSPP_RECT_1) {
					mixercfg_ext2 |= ((i + 1) & 0xF) << 20;
				} else {
					mix |= (i + 1) & 0xF;
					mixercfg_ext2 |= mix << 4;
				}
				break;
			case SSPP_CURSOR0:
				mixercfg_ext |= ((i + 1) & 0xF) << 20;
				break;
			case SSPP_CURSOR1:
				mixercfg_ext |= ((i + 1) & 0xF) << 26;
				break;
			default:
				break;
			}
		}
	}

exit:
	DPU_REG_WRITE(c, CTL_LAYER(lm), mixercfg);
	DPU_REG_WRITE(c, CTL_LAYER_EXT(lm), mixercfg_ext);
	DPU_REG_WRITE(c, CTL_LAYER_EXT2(lm), mixercfg_ext2);
	DPU_REG_WRITE(c, CTL_LAYER_EXT3(lm), mixercfg_ext3);
}
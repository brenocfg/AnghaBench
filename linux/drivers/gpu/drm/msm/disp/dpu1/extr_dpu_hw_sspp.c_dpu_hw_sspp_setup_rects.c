#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* plane_pitch; } ;
struct TYPE_5__ {int y1; int x1; } ;
struct dpu_hw_pipe_cfg {TYPE_1__ layout; TYPE_2__ dst_rect; TYPE_2__ src_rect; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pipe {struct dpu_hw_blk_reg_map hw; } ;
typedef  enum dpu_sspp_multirect_index { ____Placeholder_dpu_sspp_multirect_index } dpu_sspp_multirect_index ;

/* Variables and functions */
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int,int) ; 
 int DPU_SSPP_RECT_0 ; 
 int DPU_SSPP_RECT_SOLO ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 int SSPP_OUT_SIZE ; 
 int SSPP_OUT_SIZE_REC1 ; 
 int SSPP_OUT_XY ; 
 int SSPP_OUT_XY_REC1 ; 
 int SSPP_SRC_SIZE ; 
 int SSPP_SRC_SIZE_REC1 ; 
 int SSPP_SRC_XY ; 
 int SSPP_SRC_XY_REC1 ; 
 int SSPP_SRC_YSTRIDE0 ; 
 int SSPP_SRC_YSTRIDE1 ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,int*) ; 
 int drm_rect_height (TYPE_2__*) ; 
 int drm_rect_width (TYPE_2__*) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_rects(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pipe_cfg *cfg,
		enum dpu_sspp_multirect_index rect_index)
{
	struct dpu_hw_blk_reg_map *c;
	u32 src_size, src_xy, dst_size, dst_xy, ystride0, ystride1;
	u32 src_size_off, src_xy_off, out_size_off, out_xy_off;
	u32 idx;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx) || !cfg)
		return;

	c = &ctx->hw;

	if (rect_index == DPU_SSPP_RECT_SOLO || rect_index == DPU_SSPP_RECT_0) {
		src_size_off = SSPP_SRC_SIZE;
		src_xy_off = SSPP_SRC_XY;
		out_size_off = SSPP_OUT_SIZE;
		out_xy_off = SSPP_OUT_XY;
	} else {
		src_size_off = SSPP_SRC_SIZE_REC1;
		src_xy_off = SSPP_SRC_XY_REC1;
		out_size_off = SSPP_OUT_SIZE_REC1;
		out_xy_off = SSPP_OUT_XY_REC1;
	}


	/* src and dest rect programming */
	src_xy = (cfg->src_rect.y1 << 16) | cfg->src_rect.x1;
	src_size = (drm_rect_height(&cfg->src_rect) << 16) |
		   drm_rect_width(&cfg->src_rect);
	dst_xy = (cfg->dst_rect.y1 << 16) | cfg->dst_rect.x1;
	dst_size = (drm_rect_height(&cfg->dst_rect) << 16) |
		drm_rect_width(&cfg->dst_rect);

	if (rect_index == DPU_SSPP_RECT_SOLO) {
		ystride0 = (cfg->layout.plane_pitch[0]) |
			(cfg->layout.plane_pitch[1] << 16);
		ystride1 = (cfg->layout.plane_pitch[2]) |
			(cfg->layout.plane_pitch[3] << 16);
	} else {
		ystride0 = DPU_REG_READ(c, SSPP_SRC_YSTRIDE0 + idx);
		ystride1 = DPU_REG_READ(c, SSPP_SRC_YSTRIDE1 + idx);

		if (rect_index == DPU_SSPP_RECT_0) {
			ystride0 = (ystride0 & 0xFFFF0000) |
				(cfg->layout.plane_pitch[0] & 0x0000FFFF);
			ystride1 = (ystride1 & 0xFFFF0000)|
				(cfg->layout.plane_pitch[2] & 0x0000FFFF);
		} else {
			ystride0 = (ystride0 & 0x0000FFFF) |
				((cfg->layout.plane_pitch[0] << 16) &
				 0xFFFF0000);
			ystride1 = (ystride1 & 0x0000FFFF) |
				((cfg->layout.plane_pitch[2] << 16) &
				 0xFFFF0000);
		}
	}

	/* rectangle register programming */
	DPU_REG_WRITE(c, src_size_off + idx, src_size);
	DPU_REG_WRITE(c, src_xy_off + idx, src_xy);
	DPU_REG_WRITE(c, out_size_off + idx, dst_size);
	DPU_REG_WRITE(c, out_xy_off + idx, dst_xy);

	DPU_REG_WRITE(c, SSPP_SRC_YSTRIDE0 + idx, ystride0);
	DPU_REG_WRITE(c, SSPP_SRC_YSTRIDE1 + idx, ystride1);
}
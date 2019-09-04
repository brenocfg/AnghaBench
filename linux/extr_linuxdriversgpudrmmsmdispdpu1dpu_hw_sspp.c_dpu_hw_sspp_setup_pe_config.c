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
typedef  int u8 ;
typedef  int u32 ;
struct dpu_hw_pixel_ext {int const* right_ftch; int const* right_rpt; int const* left_ftch; int const* left_rpt; int const* btm_ftch; int const* btm_rpt; int const* top_ftch; int const* top_rpt; int const* roi_h; int const* num_ext_pxls_top; int const* num_ext_pxls_btm; int const* roi_w; int const* num_ext_pxls_left; int const* num_ext_pxls_right; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_pipe {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int DPU_MAX_PLANES ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int,int) ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 int SSPP_SW_PIX_EXT_C0_LR ; 
 int SSPP_SW_PIX_EXT_C0_REQ_PIXELS ; 
 int SSPP_SW_PIX_EXT_C0_TB ; 
 int SSPP_SW_PIX_EXT_C1C2_LR ; 
 int SSPP_SW_PIX_EXT_C1C2_REQ_PIXELS ; 
 int SSPP_SW_PIX_EXT_C1C2_TB ; 
 int SSPP_SW_PIX_EXT_C3_LR ; 
 int SSPP_SW_PIX_EXT_C3_REQ_PIXELS ; 
 int SSPP_SW_PIX_EXT_C3_TB ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_pe_config(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pixel_ext *pe_ext)
{
	struct dpu_hw_blk_reg_map *c;
	u8 color;
	u32 lr_pe[4], tb_pe[4], tot_req_pixels[4];
	const u32 bytemask = 0xff;
	const u32 shortmask = 0xffff;
	u32 idx;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx) || !pe_ext)
		return;

	c = &ctx->hw;

	/* program SW pixel extension override for all pipes*/
	for (color = 0; color < DPU_MAX_PLANES; color++) {
		/* color 2 has the same set of registers as color 1 */
		if (color == 2)
			continue;

		lr_pe[color] = ((pe_ext->right_ftch[color] & bytemask) << 24)|
			((pe_ext->right_rpt[color] & bytemask) << 16)|
			((pe_ext->left_ftch[color] & bytemask) << 8)|
			(pe_ext->left_rpt[color] & bytemask);

		tb_pe[color] = ((pe_ext->btm_ftch[color] & bytemask) << 24)|
			((pe_ext->btm_rpt[color] & bytemask) << 16)|
			((pe_ext->top_ftch[color] & bytemask) << 8)|
			(pe_ext->top_rpt[color] & bytemask);

		tot_req_pixels[color] = (((pe_ext->roi_h[color] +
			pe_ext->num_ext_pxls_top[color] +
			pe_ext->num_ext_pxls_btm[color]) & shortmask) << 16) |
			((pe_ext->roi_w[color] +
			pe_ext->num_ext_pxls_left[color] +
			pe_ext->num_ext_pxls_right[color]) & shortmask);
	}

	/* color 0 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_LR + idx, lr_pe[0]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_TB + idx, tb_pe[0]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C0_REQ_PIXELS + idx,
			tot_req_pixels[0]);

	/* color 1 and color 2 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_LR + idx, lr_pe[1]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_TB + idx, tb_pe[1]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C1C2_REQ_PIXELS + idx,
			tot_req_pixels[1]);

	/* color 3 */
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_LR + idx, lr_pe[3]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_TB + idx, lr_pe[3]);
	DPU_REG_WRITE(c, SSPP_SW_PIX_EXT_C3_REQ_PIXELS + idx,
			tot_req_pixels[3]);
}
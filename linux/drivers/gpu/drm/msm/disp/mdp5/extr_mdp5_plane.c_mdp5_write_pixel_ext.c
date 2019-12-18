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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  pixel_format; } ;
struct mdp_format {scalar_t__ is_yuv; TYPE_1__ base; } ;
struct mdp5_kms {int dummy; } ;
struct drm_format_info {int hsub; int vsub; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int COMP_1_2 ; 
 int COMP_MAX ; 
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD (int,int (*) (int)) ; 
 int MDP5_PIPE_SW_PIX_EXT_LR_LEFT_OVF (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_LR_LEFT_RPT (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_OVF (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_RPT (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_LEFT_RIGHT (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_TOP_BOTTOM (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_OVF (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_RPT (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_TB_TOP_OVF (int) ; 
 int MDP5_PIPE_SW_PIX_EXT_TB_TOP_RPT (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SW_PIX_EXT_LR (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SW_PIX_EXT_TB (int,int) ; 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mdp5_write_pixel_ext(struct mdp5_kms *mdp5_kms, enum mdp5_pipe pipe,
	const struct mdp_format *format,
	uint32_t src_w, int pe_left[COMP_MAX], int pe_right[COMP_MAX],
	uint32_t src_h, int pe_top[COMP_MAX], int pe_bottom[COMP_MAX])
{
	const struct drm_format_info *info = drm_format_info(format->base.pixel_format);
	uint32_t lr, tb, req;
	int i;

	for (i = 0; i < COMP_MAX; i++) {
		uint32_t roi_w = src_w;
		uint32_t roi_h = src_h;

		if (format->is_yuv && i == COMP_1_2) {
			roi_w /= info->hsub;
			roi_h /= info->vsub;
		}

		lr  = (pe_left[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_LR_LEFT_RPT(pe_left[i]) :
			MDP5_PIPE_SW_PIX_EXT_LR_LEFT_OVF(pe_left[i]);

		lr |= (pe_right[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_RPT(pe_right[i]) :
			MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_OVF(pe_right[i]);

		tb  = (pe_top[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_TB_TOP_RPT(pe_top[i]) :
			MDP5_PIPE_SW_PIX_EXT_TB_TOP_OVF(pe_top[i]);

		tb |= (pe_bottom[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_RPT(pe_bottom[i]) :
			MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_OVF(pe_bottom[i]);

		req  = MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_LEFT_RIGHT(roi_w +
				pe_left[i] + pe_right[i]);

		req |= MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_TOP_BOTTOM(roi_h +
				pe_top[i] + pe_bottom[i]);

		mdp5_write(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_LR(pipe, i), lr);
		mdp5_write(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_TB(pipe, i), tb);
		mdp5_write(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS(pipe, i), req);

		DBG("comp-%d (L/R): rpt=%d/%d, ovf=%d/%d, req=%d", i,
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_LEFT_RPT),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_RPT),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_LEFT_OVF),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_OVF),
			FIELD(req, MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_LEFT_RIGHT));

		DBG("comp-%d (T/B): rpt=%d/%d, ovf=%d/%d, req=%d", i,
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_TOP_RPT),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_RPT),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_TOP_OVF),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_OVF),
			FIELD(req, MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_TOP_BOTTOM));
	}
}
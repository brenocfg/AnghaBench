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
struct s5p_mfc_regs {scalar_t__ e_fixed_picture_qp; scalar_t__ e_rc_qp_bound; scalar_t__ e_rc_frame_rate; scalar_t__ e_rc_config; scalar_t__ e_hier_bit_rate_layer0; scalar_t__ e_hier_qp_layer0; scalar_t__ e_num_t_layer; scalar_t__ e_hevc_lf_tc_offset_div2; scalar_t__ e_hevc_lf_beta_offset_div2; scalar_t__ e_hevc_refresh_period; scalar_t__ e_hevc_options; scalar_t__ e_picture_profile; scalar_t__ e_gop_config; } ;
struct s5p_mfc_hevc_enc_params {int level; int tier; int profile; int loopfilter; int loopfilter_disable; int loopfilter_across; int max_partition_depth; int num_refs_for_p; int refreshtype; int const_intra_period_enable; int lossless_cu_enable; int wavefront_enable; int enable_ltr; int hier_qp_enable; int general_pb_enable; int temporal_id_enable; int strong_intra_smooth; int intra_pu_split_disable; int tmv_prediction_disable; int max_num_merge_mv; int encoding_nostartcode_enable; int prepend_sps_pps_to_idr; int refreshperiod; unsigned int lf_beta_offset_div2; unsigned int lf_tc_offset_div2; int num_hier_layer; int hier_qp_type; unsigned int* hier_qp_layer; unsigned int* hier_bit_layer; unsigned int rc_frame_qp; int rc_framerate; int rc_max_qp; unsigned int rc_min_qp; int rc_b_frame_qp; int rc_p_frame_qp; } ;
struct TYPE_2__ {struct s5p_mfc_hevc_enc_params hevc; } ;
struct s5p_mfc_enc_params {int num_b_frame; int rc_mb; scalar_t__ rc_frame; TYPE_1__ codec; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {int img_width; int img_height; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int FRAME_DELTA_DEFAULT ; 
#define  V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED 130 
#define  V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY 129 
#define  V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_ENABLED 128 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params_hevc(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_hevc_enc_params *p_hevc = &p->codec.hevc;
	unsigned int reg = 0;
	int i;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = readl(mfc_regs->e_gop_config);
	/* num_b_frame - 0 ~ 2 */
	reg &= ~(0x3 << 16);
	reg |= (p->num_b_frame << 16);
	writel(reg, mfc_regs->e_gop_config);

	/* UHD encoding case */
	if ((ctx->img_width == 3840) && (ctx->img_height == 2160)) {
		p_hevc->level = 51;
		p_hevc->tier = 0;
	/* this tier can be changed */
	}

	/* tier & level */
	reg = 0;
	/* profile */
	reg |= p_hevc->profile & 0x3;
	/* level */
	reg &= ~(0xFF << 8);
	reg |= (p_hevc->level << 8);
	/* tier - 0 ~ 1 */
	reg |= (p_hevc->tier << 16);
	writel(reg, mfc_regs->e_picture_profile);

	switch (p_hevc->loopfilter) {
	case V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED:
		p_hevc->loopfilter_disable = 1;
		break;
	case V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_ENABLED:
		p_hevc->loopfilter_disable = 0;
		p_hevc->loopfilter_across = 1;
		break;
	case V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY:
		p_hevc->loopfilter_disable = 0;
		p_hevc->loopfilter_across = 0;
		break;
	}

	/* max partition depth */
	reg = 0;
	reg |= (p_hevc->max_partition_depth & 0x1);
	reg |= (p_hevc->num_refs_for_p-1) << 2;
	reg |= (p_hevc->refreshtype & 0x3) << 3;
	reg |= (p_hevc->const_intra_period_enable & 0x1) << 5;
	reg |= (p_hevc->lossless_cu_enable & 0x1) << 6;
	reg |= (p_hevc->wavefront_enable & 0x1) << 7;
	reg |= (p_hevc->loopfilter_disable & 0x1) << 8;
	reg |= (p_hevc->loopfilter_across & 0x1) << 9;
	reg |= (p_hevc->enable_ltr & 0x1) << 10;
	reg |= (p_hevc->hier_qp_enable & 0x1) << 11;
	reg |= (p_hevc->general_pb_enable & 0x1) << 13;
	reg |= (p_hevc->temporal_id_enable & 0x1) << 14;
	reg |= (p_hevc->strong_intra_smooth & 0x1) << 15;
	reg |= (p_hevc->intra_pu_split_disable & 0x1) << 16;
	reg |= (p_hevc->tmv_prediction_disable & 0x1) << 17;
	reg |= (p_hevc->max_num_merge_mv & 0x7) << 18;
	reg |= (p_hevc->encoding_nostartcode_enable & 0x1) << 23;
	reg |= (p_hevc->prepend_sps_pps_to_idr << 26);

	writel(reg, mfc_regs->e_hevc_options);
	/* refresh period */
	if (p_hevc->refreshtype) {
		reg = 0;
		reg |= (p_hevc->refreshperiod & 0xFFFF);
		writel(reg, mfc_regs->e_hevc_refresh_period);
	}
	/* loop filter setting */
	if (!(p_hevc->loopfilter_disable & 0x1)) {
		reg = 0;
		reg |= (p_hevc->lf_beta_offset_div2);
		writel(reg, mfc_regs->e_hevc_lf_beta_offset_div2);
		reg = 0;
		reg |= (p_hevc->lf_tc_offset_div2);
		writel(reg, mfc_regs->e_hevc_lf_tc_offset_div2);
	}
	/* hier qp enable */
	if (p_hevc->num_hier_layer) {
		reg = 0;
		reg |= (p_hevc->hier_qp_type & 0x1) << 0x3;
		reg |= p_hevc->num_hier_layer & 0x7;
		writel(reg, mfc_regs->e_num_t_layer);
		/* QP value for each layer */
		if (p_hevc->hier_qp_enable) {
			for (i = 0; i < 7; i++)
				writel(p_hevc->hier_qp_layer[i],
					mfc_regs->e_hier_qp_layer0 + i * 4);
		}
		if (p->rc_frame) {
			for (i = 0; i < 7; i++)
				writel(p_hevc->hier_bit_layer[i],
						mfc_regs->e_hier_bit_rate_layer0
						+ i * 4);
		}
	}

	/* rate control config. */
	reg = readl(mfc_regs->e_rc_config);
	/* macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= (p->rc_mb << 8);
	writel(reg, mfc_regs->e_rc_config);
	/* frame QP */
	reg &= ~(0xFF);
	reg |= p_hevc->rc_frame_qp;
	writel(reg, mfc_regs->e_rc_config);

	/* frame rate */
	if (p->rc_frame) {
		reg = 0;
		reg &= ~(0xFFFF << 16);
		reg |= ((p_hevc->rc_framerate) << 16);
		reg &= ~(0xFFFF);
		reg |= FRAME_DELTA_DEFAULT;
		writel(reg, mfc_regs->e_rc_frame_rate);
	}

	/* max & min value of QP */
	reg = 0;
	/* max QP */
	reg &= ~(0xFF << 8);
	reg |= (p_hevc->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0xFF);
	reg |= p_hevc->rc_min_qp;
	writel(reg, mfc_regs->e_rc_qp_bound);

	writel(0x0, mfc_regs->e_fixed_picture_qp);
	if (!p->rc_frame && !p->rc_mb) {
		reg = 0;
		reg &= ~(0xFF << 16);
		reg |= (p_hevc->rc_b_frame_qp << 16);
		reg &= ~(0xFF << 8);
		reg |= (p_hevc->rc_p_frame_qp << 8);
		reg &= ~(0xFF);
		reg |= p_hevc->rc_frame_qp;
		writel(reg, mfc_regs->e_fixed_picture_qp);
	}
	mfc_debug_leave();

	return 0;
}
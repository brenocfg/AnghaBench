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
struct s5p_mfc_regs {int /*<<< orphan*/  e_vbv_init_delay; int /*<<< orphan*/  e_vbv_buffer_size; int /*<<< orphan*/  e_rc_frame_rate; int /*<<< orphan*/  e_fixed_picture_qp; int /*<<< orphan*/  e_rc_qp_bound; int /*<<< orphan*/  e_rc_config; int /*<<< orphan*/  e_picture_profile; } ;
struct s5p_mfc_mpeg4_enc_params {int rc_frame_qp; int rc_max_qp; int rc_min_qp; int rc_b_frame_qp; int rc_p_frame_qp; } ;
struct TYPE_2__ {struct s5p_mfc_mpeg4_enc_params mpeg4; } ;
struct s5p_mfc_enc_params {int rc_mb; int rc_framerate_num; int rc_framerate_denom; scalar_t__ frame_skip_mode; int vbv_size; int vbv_delay; scalar_t__ rc_frame; TYPE_1__ codec; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 scalar_t__ V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params_h263(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_mpeg4_enc_params *p_h263 = &p->codec.mpeg4;
	unsigned int reg = 0;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* profile & level */
	reg = 0;
	/** profile */
	reg |= (0x1 << 4);
	writel(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = readl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	writel(reg, mfc_regs->e_rc_config);

	/** frame QP */
	reg &= ~(0x3F);
	reg |= p_h263->rc_frame_qp & 0x3F;
	writel(reg, mfc_regs->e_rc_config);

	/* max & min value of QP */
	reg = 0;
	/** max QP */
	reg |= ((p_h263->rc_max_qp & 0x3F) << 8);
	/** min QP */
	reg |= p_h263->rc_min_qp & 0x3F;
	writel(reg, mfc_regs->e_rc_qp_bound);

	/* other QPs */
	writel(0x0, mfc_regs->e_fixed_picture_qp);
	if (!p->rc_frame && !p->rc_mb) {
		reg = 0;
		reg |= ((p_h263->rc_b_frame_qp & 0x3F) << 16);
		reg |= ((p_h263->rc_p_frame_qp & 0x3F) << 8);
		reg |= p_h263->rc_frame_qp & 0x3F;
		writel(reg, mfc_regs->e_fixed_picture_qp);
	}

	/* frame rate */
	if (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) {
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		writel(reg, mfc_regs->e_rc_frame_rate);
	}

	/* vbv buffer size */
	if (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) {
		writel(p->vbv_size & 0xFFFF, mfc_regs->e_vbv_buffer_size);

		if (p->rc_frame)
			writel(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	}

	mfc_debug_leave();

	return 0;
}
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
typedef  scalar_t__ u32 ;
struct v4l2_vp8_segment_header {int flags; scalar_t__* lf_update; } ;
struct v4l2_vp8_loopfilter_header {int flags; scalar_t__* ref_frm_delta; scalar_t__* mb_mode_delta; int /*<<< orphan*/  sharpness_level; scalar_t__ level; } ;
struct v4l2_ctrl_vp8_frame_header {struct v4l2_vp8_loopfilter_header lf_header; struct v4l2_vp8_segment_header segment_header; } ;
struct hantro_dev {int dummy; } ;
struct hantro_ctx {struct hantro_dev* dev; } ;

/* Variables and functions */
 int V4L2_VP8_LF_FILTER_TYPE_SIMPLE ; 
 int V4L2_VP8_LF_HEADER_ADJ_ENABLE ; 
 int V4L2_VP8_SEGMENT_HEADER_FLAG_DELTA_VALUE_MODE ; 
 int V4L2_VP8_SEGMENT_HEADER_FLAG_ENABLED ; 
 int /*<<< orphan*/  VDPU_REG_FILTER_MB_ADJ ; 
 scalar_t__ VDPU_REG_REF_PIC_FILT_SHARPNESS (int /*<<< orphan*/ ) ; 
 scalar_t__ VDPU_REG_REF_PIC_FILT_TYPE_E ; 
 scalar_t__ clamp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hantro_reg_write (struct hantro_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vp8_dec_lf_level ; 
 int /*<<< orphan*/ * vp8_dec_mb_adj ; 
 int /*<<< orphan*/ * vp8_dec_ref_adj ; 

__attribute__((used)) static void cfg_lf(struct hantro_ctx *ctx,
		   const struct v4l2_ctrl_vp8_frame_header *hdr)
{
	const struct v4l2_vp8_segment_header *seg = &hdr->segment_header;
	const struct v4l2_vp8_loopfilter_header *lf = &hdr->lf_header;
	struct hantro_dev *vpu = ctx->dev;
	unsigned int i;
	u32 reg;

	if (!(seg->flags & V4L2_VP8_SEGMENT_HEADER_FLAG_ENABLED)) {
		hantro_reg_write(vpu, &vp8_dec_lf_level[0], lf->level);
	} else if (seg->flags & V4L2_VP8_SEGMENT_HEADER_FLAG_DELTA_VALUE_MODE) {
		for (i = 0; i < 4; i++) {
			u32 lf_level = clamp(lf->level + seg->lf_update[i],
					     0, 63);

			hantro_reg_write(vpu, &vp8_dec_lf_level[i], lf_level);
		}
	} else {
		for (i = 0; i < 4; i++)
			hantro_reg_write(vpu, &vp8_dec_lf_level[i],
					 seg->lf_update[i]);
	}

	reg = VDPU_REG_REF_PIC_FILT_SHARPNESS(lf->sharpness_level);
	if (lf->flags & V4L2_VP8_LF_FILTER_TYPE_SIMPLE)
		reg |= VDPU_REG_REF_PIC_FILT_TYPE_E;
	vdpu_write_relaxed(vpu, reg, VDPU_REG_FILTER_MB_ADJ);

	if (lf->flags & V4L2_VP8_LF_HEADER_ADJ_ENABLE) {
		for (i = 0; i < 4; i++) {
			hantro_reg_write(vpu, &vp8_dec_mb_adj[i],
					 lf->mb_mode_delta[i]);
			hantro_reg_write(vpu, &vp8_dec_ref_adj[i],
					 lf->ref_frm_delta[i]);
		}
	}
}
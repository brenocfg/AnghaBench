#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  config; } ;
struct v4l2_pix_format_mplane {int num_planes; int flags; TYPE_1__* plane_fmt; } ;
struct vsp1_rwpf {int mult_alpha; int /*<<< orphan*/  brx_input; TYPE_5__ entity; struct v4l2_pix_format_mplane format; struct vsp1_format_info* fmtinfo; } ;
struct vsp1_pipeline {scalar_t__ interlaced; TYPE_4__* brx; } ;
struct vsp1_format_info {int hwfmt; unsigned int swap; scalar_t__ alpha; scalar_t__ swap_uv; scalar_t__ swap_yc; } ;
struct vsp1_entity {TYPE_3__* vsp1; int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_rect {unsigned int left; unsigned int top; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct TYPE_9__ {int /*<<< orphan*/  config; } ;
struct TYPE_8__ {TYPE_2__* info; } ;
struct TYPE_7__ {int gen; } ;
struct TYPE_6__ {int bytesperline; } ;

/* Variables and functions */
 int /*<<< orphan*/  RWPF_PAD_SINK ; 
 int /*<<< orphan*/  RWPF_PAD_SOURCE ; 
 int V4L2_PIX_FMT_FLAG_PREMUL_ALPHA ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_COMPOSE ; 
 int /*<<< orphan*/  VI6_RPF_ALPH_SEL ; 
 unsigned int VI6_RPF_ALPH_SEL_AEXT_EXT ; 
 unsigned int VI6_RPF_ALPH_SEL_ASEL_FIXED ; 
 unsigned int VI6_RPF_ALPH_SEL_ASEL_PACKED ; 
 int /*<<< orphan*/  VI6_RPF_CKEY_CTRL ; 
 int /*<<< orphan*/  VI6_RPF_DSWAP ; 
 int /*<<< orphan*/  VI6_RPF_INFMT ; 
 int VI6_RPF_INFMT_CIPM ; 
 int VI6_RPF_INFMT_CSC ; 
 int VI6_RPF_INFMT_RDFMT_SHIFT ; 
 int VI6_RPF_INFMT_SPUVS ; 
 int VI6_RPF_INFMT_SPYCS ; 
 int /*<<< orphan*/  VI6_RPF_LOC ; 
 unsigned int VI6_RPF_LOC_HCOORD_SHIFT ; 
 unsigned int VI6_RPF_LOC_VCOORD_SHIFT ; 
 int /*<<< orphan*/  VI6_RPF_MSK_CTRL ; 
 int VI6_RPF_MULT_ALPHA_A_MMD_NONE ; 
 int VI6_RPF_MULT_ALPHA_A_MMD_RATIO ; 
 int VI6_RPF_MULT_ALPHA_P_MMD_NONE ; 
 int VI6_RPF_MULT_ALPHA_P_MMD_RATIO ; 
 int /*<<< orphan*/  VI6_RPF_SRCM_PSTRIDE ; 
 int VI6_RPF_SRCM_PSTRIDE_C_SHIFT ; 
 int VI6_RPF_SRCM_PSTRIDE_Y_SHIFT ; 
 struct vsp1_rwpf* to_rwpf (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_rect* vsp1_entity_get_pad_selection (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_rpf_write (struct vsp1_rwpf*,struct vsp1_dl_body*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rpf_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	struct vsp1_rwpf *rpf = to_rwpf(&entity->subdev);
	const struct vsp1_format_info *fmtinfo = rpf->fmtinfo;
	const struct v4l2_pix_format_mplane *format = &rpf->format;
	const struct v4l2_mbus_framefmt *source_format;
	const struct v4l2_mbus_framefmt *sink_format;
	unsigned int left = 0;
	unsigned int top = 0;
	u32 pstride;
	u32 infmt;

	/* Stride */
	pstride = format->plane_fmt[0].bytesperline
		<< VI6_RPF_SRCM_PSTRIDE_Y_SHIFT;
	if (format->num_planes > 1)
		pstride |= format->plane_fmt[1].bytesperline
			<< VI6_RPF_SRCM_PSTRIDE_C_SHIFT;

	/*
	 * pstride has both STRIDE_Y and STRIDE_C, but multiplying the whole
	 * of pstride by 2 is conveniently OK here as we are multiplying both
	 * values.
	 */
	if (pipe->interlaced)
		pstride *= 2;

	vsp1_rpf_write(rpf, dlb, VI6_RPF_SRCM_PSTRIDE, pstride);

	/* Format */
	sink_format = vsp1_entity_get_pad_format(&rpf->entity,
						 rpf->entity.config,
						 RWPF_PAD_SINK);
	source_format = vsp1_entity_get_pad_format(&rpf->entity,
						   rpf->entity.config,
						   RWPF_PAD_SOURCE);

	infmt = VI6_RPF_INFMT_CIPM
	      | (fmtinfo->hwfmt << VI6_RPF_INFMT_RDFMT_SHIFT);

	if (fmtinfo->swap_yc)
		infmt |= VI6_RPF_INFMT_SPYCS;
	if (fmtinfo->swap_uv)
		infmt |= VI6_RPF_INFMT_SPUVS;

	if (sink_format->code != source_format->code)
		infmt |= VI6_RPF_INFMT_CSC;

	vsp1_rpf_write(rpf, dlb, VI6_RPF_INFMT, infmt);
	vsp1_rpf_write(rpf, dlb, VI6_RPF_DSWAP, fmtinfo->swap);

	/* Output location. */
	if (pipe->brx) {
		const struct v4l2_rect *compose;

		compose = vsp1_entity_get_pad_selection(pipe->brx,
							pipe->brx->config,
							rpf->brx_input,
							V4L2_SEL_TGT_COMPOSE);
		left = compose->left;
		top = compose->top;
	}

	if (pipe->interlaced)
		top /= 2;

	vsp1_rpf_write(rpf, dlb, VI6_RPF_LOC,
		       (left << VI6_RPF_LOC_HCOORD_SHIFT) |
		       (top << VI6_RPF_LOC_VCOORD_SHIFT));

	/*
	 * On Gen2 use the alpha channel (extended to 8 bits) when available or
	 * a fixed alpha value set through the V4L2_CID_ALPHA_COMPONENT control
	 * otherwise.
	 *
	 * The Gen3 RPF has extended alpha capability and can both multiply the
	 * alpha channel by a fixed global alpha value, and multiply the pixel
	 * components to convert the input to premultiplied alpha.
	 *
	 * As alpha premultiplication is available in the BRx for both Gen2 and
	 * Gen3 we handle it there and use the Gen3 alpha multiplier for global
	 * alpha multiplication only. This however prevents conversion to
	 * premultiplied alpha if no BRx is present in the pipeline. If that use
	 * case turns out to be useful we will revisit the implementation (for
	 * Gen3 only).
	 *
	 * We enable alpha multiplication on Gen3 using the fixed alpha value
	 * set through the V4L2_CID_ALPHA_COMPONENT control when the input
	 * contains an alpha channel. On Gen2 the global alpha is ignored in
	 * that case.
	 *
	 * In all cases, disable color keying.
	 */
	vsp1_rpf_write(rpf, dlb, VI6_RPF_ALPH_SEL, VI6_RPF_ALPH_SEL_AEXT_EXT |
		       (fmtinfo->alpha ? VI6_RPF_ALPH_SEL_ASEL_PACKED
				       : VI6_RPF_ALPH_SEL_ASEL_FIXED));

	if (entity->vsp1->info->gen == 3) {
		u32 mult;

		if (fmtinfo->alpha) {
			/*
			 * When the input contains an alpha channel enable the
			 * alpha multiplier. If the input is premultiplied we
			 * need to multiply both the alpha channel and the pixel
			 * components by the global alpha value to keep them
			 * premultiplied. Otherwise multiply the alpha channel
			 * only.
			 */
			bool premultiplied = format->flags
					   & V4L2_PIX_FMT_FLAG_PREMUL_ALPHA;

			mult = VI6_RPF_MULT_ALPHA_A_MMD_RATIO
			     | (premultiplied ?
				VI6_RPF_MULT_ALPHA_P_MMD_RATIO :
				VI6_RPF_MULT_ALPHA_P_MMD_NONE);
		} else {
			/*
			 * When the input doesn't contain an alpha channel the
			 * global alpha value is applied in the unpacking unit,
			 * the alpha multiplier isn't needed and must be
			 * disabled.
			 */
			mult = VI6_RPF_MULT_ALPHA_A_MMD_NONE
			     | VI6_RPF_MULT_ALPHA_P_MMD_NONE;
		}

		rpf->mult_alpha = mult;
	}

	vsp1_rpf_write(rpf, dlb, VI6_RPF_MSK_CTRL, 0);
	vsp1_rpf_write(rpf, dlb, VI6_RPF_CKEY_CTRL, 0);

}
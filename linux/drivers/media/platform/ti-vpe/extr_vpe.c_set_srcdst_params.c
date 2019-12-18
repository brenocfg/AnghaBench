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
struct TYPE_7__ {unsigned int width; unsigned int height; } ;
struct vpe_q_data {int flags; int width; int height; int /*<<< orphan*/  colorspace; TYPE_2__ c_rect; } ;
struct vpe_mmr_adb {int /*<<< orphan*/ * sc_regs17; int /*<<< orphan*/ * sc_regs8; int /*<<< orphan*/ * sc_regs0; int /*<<< orphan*/ * csc_regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {struct vpe_mmr_adb* addr; } ;
struct vpe_ctx {int deinterlacing; TYPE_5__* dev; TYPE_4__ sc_coeff_v; TYPE_3__ sc_coeff_h; int /*<<< orphan*/ ** src_vbs; int /*<<< orphan*/  field; scalar_t__ sequence; TYPE_1__ mmr_adb; struct vpe_q_data* q_data; } ;
struct vpdma_data_format {int depth; } ;
struct TYPE_10__ {int /*<<< orphan*/  sc; int /*<<< orphan*/  csc; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 size_t Q_DATA_DST ; 
 size_t Q_DATA_SRC ; 
 int Q_IS_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_TOP ; 
 size_t VPDMA_DATA_FMT_MV ; 
 int /*<<< orphan*/  VPDMA_STRIDE_ALIGN ; 
 int /*<<< orphan*/  csc_set_coeff (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vbs (struct vpe_ctx*) ; 
 int realloc_mv_buffers (struct vpe_ctx*,size_t) ; 
 int /*<<< orphan*/  sc_config_scaler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sc_set_hs_coeffs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sc_set_vs_coeffs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_cfg_modes (struct vpe_ctx*) ; 
 int /*<<< orphan*/  set_dei_regs (struct vpe_ctx*) ; 
 struct vpdma_data_format* vpdma_misc_fmts ; 

__attribute__((used)) static int set_srcdst_params(struct vpe_ctx *ctx)
{
	struct vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SRC];
	struct vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	unsigned int src_w = s_q_data->c_rect.width;
	unsigned int src_h = s_q_data->c_rect.height;
	unsigned int dst_w = d_q_data->c_rect.width;
	unsigned int dst_h = d_q_data->c_rect.height;
	size_t mv_buf_size;
	int ret;

	ctx->sequence = 0;
	ctx->field = V4L2_FIELD_TOP;

	if ((s_q_data->flags & Q_IS_INTERLACED) &&
			!(d_q_data->flags & Q_IS_INTERLACED)) {
		int bytes_per_line;
		const struct vpdma_data_format *mv =
			&vpdma_misc_fmts[VPDMA_DATA_FMT_MV];

		/*
		 * we make sure that the source image has a 16 byte aligned
		 * stride, we need to do the same for the motion vector buffer
		 * by aligning it's stride to the next 16 byte boundary. this
		 * extra space will not be used by the de-interlacer, but will
		 * ensure that vpdma operates correctly
		 */
		bytes_per_line = ALIGN((s_q_data->width * mv->depth) >> 3,
					VPDMA_STRIDE_ALIGN);
		mv_buf_size = bytes_per_line * s_q_data->height;

		ctx->deinterlacing = true;
		src_h <<= 1;
	} else {
		ctx->deinterlacing = false;
		mv_buf_size = 0;
	}

	free_vbs(ctx);
	ctx->src_vbs[2] = ctx->src_vbs[1] = ctx->src_vbs[0] = NULL;

	ret = realloc_mv_buffers(ctx, mv_buf_size);
	if (ret)
		return ret;

	set_cfg_modes(ctx);
	set_dei_regs(ctx);

	csc_set_coeff(ctx->dev->csc, &mmr_adb->csc_regs[0],
		s_q_data->colorspace, d_q_data->colorspace);

	sc_set_hs_coeffs(ctx->dev->sc, ctx->sc_coeff_h.addr, src_w, dst_w);
	sc_set_vs_coeffs(ctx->dev->sc, ctx->sc_coeff_v.addr, src_h, dst_h);

	sc_config_scaler(ctx->dev->sc, &mmr_adb->sc_regs0[0],
		&mmr_adb->sc_regs8[0], &mmr_adb->sc_regs17[0],
		src_w, src_h, dst_w, dst_h);

	return 0;
}
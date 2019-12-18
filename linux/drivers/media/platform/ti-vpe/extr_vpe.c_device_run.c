#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vpe_q_data {int flags; scalar_t__ colorspace; TYPE_1__* fmt; } ;
struct TYPE_15__ {scalar_t__ dma_addr; } ;
struct TYPE_14__ {TYPE_5__ buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {int sequence; int load_mmrs; TYPE_4__ desc_list; TYPE_3__* dev; scalar_t__ deinterlacing; TYPE_5__ sc_coeff_v; TYPE_5__ sc_coeff_h; TYPE_5__ mmr_adb; int /*<<< orphan*/ ** src_vbs; int /*<<< orphan*/ * dst_vb; TYPE_2__ fh; struct vpe_q_data* q_data; } ;
struct sc_data {scalar_t__ loaded_coeff_h; int load_coeff_h; scalar_t__ loaded_coeff_v; int load_coeff_v; } ;
struct TYPE_13__ {scalar_t__ loaded_mmrs; int /*<<< orphan*/  vpdma; struct sc_data* sc; } ;
struct TYPE_11__ {scalar_t__ coplanar; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFD_MMR_CLIENT ; 
 int /*<<< orphan*/  CFD_SC_CLIENT ; 
 size_t Q_DATA_DST ; 
 int Q_DATA_INTERLACED_SEQ_TB ; 
 size_t Q_DATA_SRC ; 
 int SC_COEF_SRAM_SIZE ; 
 scalar_t__ V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA1_IN ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA2_IN ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA3_IN ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA_OUT ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA1_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA2_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA3_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA_OUT ; 
 int /*<<< orphan*/  VPE_CHAN_MV_IN ; 
 int /*<<< orphan*/  VPE_CHAN_MV_OUT ; 
 int /*<<< orphan*/  VPE_CHAN_RGB_OUT ; 
 int /*<<< orphan*/  VPE_PORT_CHROMA1_IN ; 
 int /*<<< orphan*/  VPE_PORT_CHROMA2_IN ; 
 int /*<<< orphan*/  VPE_PORT_CHROMA3_IN ; 
 int /*<<< orphan*/  VPE_PORT_CHROMA_OUT ; 
 int /*<<< orphan*/  VPE_PORT_LUMA1_IN ; 
 int /*<<< orphan*/  VPE_PORT_LUMA2_IN ; 
 int /*<<< orphan*/  VPE_PORT_LUMA3_IN ; 
 int /*<<< orphan*/  VPE_PORT_LUMA_OUT ; 
 int /*<<< orphan*/  VPE_PORT_MV_IN ; 
 int /*<<< orphan*/  VPE_PORT_MV_OUT ; 
 int /*<<< orphan*/  VPE_PORT_RGB_OUT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_in_dtd (struct vpe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_out_dtd (struct vpe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_edi_input_mode (struct vpe_ctx*,int) ; 
 int /*<<< orphan*/  enable_irqs (struct vpe_ctx*) ; 
 int /*<<< orphan*/  set_line_modes (struct vpe_ctx*) ; 
 int /*<<< orphan*/ * v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpdma_add_cfd_adb (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  vpdma_add_cfd_block (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  vpdma_add_sync_on_channel_ctd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpdma_map_desc_buf (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  vpdma_submit_descs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_run(void *priv)
{
	struct vpe_ctx *ctx = priv;
	struct sc_data *sc = ctx->dev->sc;
	struct vpe_q_data *d_q_data = &ctx->q_data[Q_DATA_DST];
	struct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];

	if (ctx->deinterlacing && s_q_data->flags & Q_DATA_INTERLACED_SEQ_TB &&
		ctx->sequence % 2 == 0) {
		/* When using SEQ_TB buffers, When using it first time,
		 * No need to remove the buffer as the next field is present
		 * in the same buffer. (so that job_ready won't fail)
		 * It will be removed when using bottom field
		 */
		ctx->src_vbs[0] = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		WARN_ON(ctx->src_vbs[0] == NULL);
	} else {
		ctx->src_vbs[0] = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		WARN_ON(ctx->src_vbs[0] == NULL);
	}

	ctx->dst_vb = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	WARN_ON(ctx->dst_vb == NULL);

	if (ctx->deinterlacing) {

		if (ctx->src_vbs[2] == NULL) {
			ctx->src_vbs[2] = ctx->src_vbs[0];
			WARN_ON(ctx->src_vbs[2] == NULL);
			ctx->src_vbs[1] = ctx->src_vbs[0];
			WARN_ON(ctx->src_vbs[1] == NULL);
		}

		/*
		 * we have output the first 2 frames through line average, we
		 * now switch to EDI de-interlacer
		 */
		if (ctx->sequence == 2)
			config_edi_input_mode(ctx, 0x3); /* EDI (Y + UV) */
	}

	/* config descriptors */
	if (ctx->dev->loaded_mmrs != ctx->mmr_adb.dma_addr || ctx->load_mmrs) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->mmr_adb);
		vpdma_add_cfd_adb(&ctx->desc_list, CFD_MMR_CLIENT, &ctx->mmr_adb);

		set_line_modes(ctx);

		ctx->dev->loaded_mmrs = ctx->mmr_adb.dma_addr;
		ctx->load_mmrs = false;
	}

	if (sc->loaded_coeff_h != ctx->sc_coeff_h.dma_addr ||
			sc->load_coeff_h) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_h);
		vpdma_add_cfd_block(&ctx->desc_list, CFD_SC_CLIENT,
			&ctx->sc_coeff_h, 0);

		sc->loaded_coeff_h = ctx->sc_coeff_h.dma_addr;
		sc->load_coeff_h = false;
	}

	if (sc->loaded_coeff_v != ctx->sc_coeff_v.dma_addr ||
			sc->load_coeff_v) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_v);
		vpdma_add_cfd_block(&ctx->desc_list, CFD_SC_CLIENT,
			&ctx->sc_coeff_v, SC_COEF_SRAM_SIZE >> 4);

		sc->loaded_coeff_v = ctx->sc_coeff_v.dma_addr;
		sc->load_coeff_v = false;
	}

	/* output data descriptors */
	if (ctx->deinterlacing)
		add_out_dtd(ctx, VPE_PORT_MV_OUT);

	if (d_q_data->colorspace == V4L2_COLORSPACE_SRGB) {
		add_out_dtd(ctx, VPE_PORT_RGB_OUT);
	} else {
		add_out_dtd(ctx, VPE_PORT_LUMA_OUT);
		if (d_q_data->fmt->coplanar)
			add_out_dtd(ctx, VPE_PORT_CHROMA_OUT);
	}

	/* input data descriptors */
	if (ctx->deinterlacing) {
		add_in_dtd(ctx, VPE_PORT_LUMA3_IN);
		add_in_dtd(ctx, VPE_PORT_CHROMA3_IN);

		add_in_dtd(ctx, VPE_PORT_LUMA2_IN);
		add_in_dtd(ctx, VPE_PORT_CHROMA2_IN);
	}

	add_in_dtd(ctx, VPE_PORT_LUMA1_IN);
	add_in_dtd(ctx, VPE_PORT_CHROMA1_IN);

	if (ctx->deinterlacing)
		add_in_dtd(ctx, VPE_PORT_MV_IN);

	/* sync on channel control descriptors for input ports */
	vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_LUMA1_IN);
	vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_CHROMA1_IN);

	if (ctx->deinterlacing) {
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA2_IN);
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_CHROMA2_IN);

		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA3_IN);
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_CHROMA3_IN);

		vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_MV_IN);
	}

	/* sync on channel control descriptors for output ports */
	if (d_q_data->colorspace == V4L2_COLORSPACE_SRGB) {
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_RGB_OUT);
	} else {
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
			VPE_CHAN_LUMA_OUT);
		if (d_q_data->fmt->coplanar)
			vpdma_add_sync_on_channel_ctd(&ctx->desc_list,
				VPE_CHAN_CHROMA_OUT);
	}

	if (ctx->deinterlacing)
		vpdma_add_sync_on_channel_ctd(&ctx->desc_list, VPE_CHAN_MV_OUT);

	enable_irqs(ctx);

	vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->desc_list.buf);
	vpdma_submit_descs(ctx->dev->vpdma, &ctx->desc_list, 0);
}
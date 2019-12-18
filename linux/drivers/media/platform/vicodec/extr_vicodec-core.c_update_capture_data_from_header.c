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
struct vicodec_q_data {int coded_width; int coded_height; int sizeimage; struct v4l2_fwht_pixfmt_info const* info; void* visible_height; void* visible_width; } ;
struct fwht_cframe_hdr {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; struct fwht_cframe_hdr header; } ;
struct vicodec_ctx {TYPE_1__ state; int /*<<< orphan*/  is_stateless; } ;
struct v4l2_fwht_pixfmt_info {int sizeimage_mult; int sizeimage_div; } ;

/* Variables and functions */
 unsigned int FWHT_FL_CHROMA_FULL_HEIGHT ; 
 unsigned int FWHT_FL_CHROMA_FULL_WIDTH ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 
 struct v4l2_fwht_pixfmt_info* info_from_header (struct fwht_cframe_hdr const*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* vic_round_dim (void*,unsigned int) ; 

__attribute__((used)) static void update_capture_data_from_header(struct vicodec_ctx *ctx)
{
	struct vicodec_q_data *q_dst = get_q_data(ctx,
						  V4L2_BUF_TYPE_VIDEO_CAPTURE);
	const struct fwht_cframe_hdr *p_hdr = &ctx->state.header;
	const struct v4l2_fwht_pixfmt_info *info = info_from_header(p_hdr);
	unsigned int flags = ntohl(p_hdr->flags);
	unsigned int hdr_width_div = (flags & FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	unsigned int hdr_height_div = (flags & FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;

	/*
	 * This function should not be used by a stateless codec since
	 * it changes values in q_data that are not request specific
	 */
	WARN_ON(ctx->is_stateless);

	q_dst->info = info;
	q_dst->visible_width = ntohl(p_hdr->width);
	q_dst->visible_height = ntohl(p_hdr->height);
	q_dst->coded_width = vic_round_dim(q_dst->visible_width, hdr_width_div);
	q_dst->coded_height = vic_round_dim(q_dst->visible_height,
					    hdr_height_div);

	q_dst->sizeimage = q_dst->coded_width * q_dst->coded_height *
		q_dst->info->sizeimage_mult / q_dst->info->sizeimage_div;
	ctx->state.colorspace = ntohl(p_hdr->colorspace);

	ctx->state.xfer_func = ntohl(p_hdr->xfer_func);
	ctx->state.ycbcr_enc = ntohl(p_hdr->ycbcr_enc);
	ctx->state.quantization = ntohl(p_hdr->quantization);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct vicodec_q_data {unsigned int width; unsigned int height; int fourcc; scalar_t__ flags; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cb; int /*<<< orphan*/ * cr; int /*<<< orphan*/ * luma; } ;
struct vicodec_ctx {TYPE_1__ ref_frame; scalar_t__ quantization; scalar_t__ ycbcr_enc; scalar_t__ xfer_func; scalar_t__ colorspace; } ;
struct cframe_hdr {scalar_t__ magic1; scalar_t__ magic2; int /*<<< orphan*/  version; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cframe {int width; int height; int /*<<< orphan*/ * rlc_data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV21 130 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YVU420 128 
 scalar_t__ VICODEC_MAGIC1 ; 
 scalar_t__ VICODEC_MAGIC2 ; 
 int VICODEC_MAX_HEIGHT ; 
 int VICODEC_MAX_WIDTH ; 
 int VICODEC_MIN_HEIGHT ; 
 int VICODEC_MIN_WIDTH ; 
 scalar_t__ VICODEC_VERSION ; 
 int /*<<< orphan*/  decode_frame (struct cframe*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode(struct vicodec_ctx *ctx,
		  struct vicodec_q_data *q_data,
		  u8 *p_in, u8 *p_out)
{
	unsigned int size = q_data->width * q_data->height;
	unsigned int i;
	struct cframe_hdr *p_hdr;
	struct cframe cf;
	u8 *p;

	p_hdr = (struct cframe_hdr *)p_in;
	cf.width = ntohl(p_hdr->width);
	cf.height = ntohl(p_hdr->height);
	q_data->flags = ntohl(p_hdr->flags);
	ctx->colorspace = ntohl(p_hdr->colorspace);
	ctx->xfer_func = ntohl(p_hdr->xfer_func);
	ctx->ycbcr_enc = ntohl(p_hdr->ycbcr_enc);
	ctx->quantization = ntohl(p_hdr->quantization);
	cf.rlc_data = (__be16 *)(p_in + sizeof(*p_hdr));

	if (p_hdr->magic1 != VICODEC_MAGIC1 ||
	    p_hdr->magic2 != VICODEC_MAGIC2 ||
	    ntohl(p_hdr->version) != VICODEC_VERSION ||
	    cf.width < VICODEC_MIN_WIDTH ||
	    cf.width > VICODEC_MAX_WIDTH ||
	    cf.height < VICODEC_MIN_HEIGHT ||
	    cf.height > VICODEC_MAX_HEIGHT ||
	    (cf.width & 7) || (cf.height & 7))
		return -EINVAL;

	/* TODO: support resolution changes */
	if (cf.width != q_data->width || cf.height != q_data->height)
		return -EINVAL;

	decode_frame(&cf, &ctx->ref_frame, q_data->flags);
	memcpy(p_out, ctx->ref_frame.luma, size);
	p_out += size;

	switch (q_data->fourcc) {
	case V4L2_PIX_FMT_YUV420:
		memcpy(p_out, ctx->ref_frame.cb, size / 4);
		p_out += size / 4;
		memcpy(p_out, ctx->ref_frame.cr, size / 4);
		break;
	case V4L2_PIX_FMT_YVU420:
		memcpy(p_out, ctx->ref_frame.cr, size / 4);
		p_out += size / 4;
		memcpy(p_out, ctx->ref_frame.cb, size / 4);
		break;
	case V4L2_PIX_FMT_NV12:
		for (i = 0, p = p_out; i < size / 4; i++, p += 2)
			*p = ctx->ref_frame.cb[i];
		for (i = 0, p = p_out + 1; i < size / 4; i++, p += 2)
			*p = ctx->ref_frame.cr[i];
		break;
	case V4L2_PIX_FMT_NV21:
		for (i = 0, p = p_out; i < size / 4; i++, p += 2)
			*p = ctx->ref_frame.cr[i];
		for (i = 0, p = p_out + 1; i < size / 4; i++, p += 2)
			*p = ctx->ref_frame.cb[i];
		break;
	}
	return 0;
}
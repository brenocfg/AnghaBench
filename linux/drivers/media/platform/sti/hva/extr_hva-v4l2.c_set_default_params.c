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
struct hva_streaminfo {void* height; void* width; int /*<<< orphan*/  streamformat; } ;
struct hva_frameinfo {int /*<<< orphan*/  pixelformat; void* aligned_height; void* aligned_width; int /*<<< orphan*/  size; void* height; void* width; } ;
struct hva_ctx {int /*<<< orphan*/  max_stream_size; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; struct hva_streaminfo streaminfo; struct hva_frameinfo frameinfo; } ;

/* Variables and functions */
 void* ALIGN (void*,int /*<<< orphan*/ ) ; 
 void* HVA_DEFAULT_HEIGHT ; 
 void* HVA_DEFAULT_WIDTH ; 
 int /*<<< orphan*/  HVA_HEIGHT_ALIGNMENT ; 
 int /*<<< orphan*/  HVA_WIDTH_ALIGNMENT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  estimated_stream_size (void*,void*) ; 
 int /*<<< orphan*/  frame_size (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_default_params(struct hva_ctx *ctx)
{
	struct hva_frameinfo *frameinfo = &ctx->frameinfo;
	struct hva_streaminfo *streaminfo = &ctx->streaminfo;

	frameinfo->pixelformat = V4L2_PIX_FMT_NV12;
	frameinfo->width = HVA_DEFAULT_WIDTH;
	frameinfo->height = HVA_DEFAULT_HEIGHT;
	frameinfo->aligned_width = ALIGN(frameinfo->width,
					 HVA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(frameinfo->height,
					  HVA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelformat);

	streaminfo->streamformat = V4L2_PIX_FMT_H264;
	streaminfo->width = HVA_DEFAULT_WIDTH;
	streaminfo->height = HVA_DEFAULT_HEIGHT;

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;

	ctx->max_stream_size = estimated_stream_size(streaminfo->width,
						     streaminfo->height);
}
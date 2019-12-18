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
struct delta_streaminfo {void* height; void* width; void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; void* field; int /*<<< orphan*/  streamformat; int /*<<< orphan*/  pixelformat; void* aligned_height; void* aligned_width; int /*<<< orphan*/  size; } ;
struct delta_frameinfo {void* height; void* width; void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; void* field; int /*<<< orphan*/  streamformat; int /*<<< orphan*/  pixelformat; void* aligned_height; void* aligned_width; int /*<<< orphan*/  size; } ;
struct delta_ctx {int /*<<< orphan*/  max_au_size; struct delta_streaminfo streaminfo; struct delta_streaminfo frameinfo; } ;

/* Variables and functions */
 void* ALIGN (void*,int /*<<< orphan*/ ) ; 
 void* DELTA_DEFAULT_HEIGHT ; 
 int /*<<< orphan*/  DELTA_DEFAULT_STREAMFORMAT ; 
 void* DELTA_DEFAULT_WIDTH ; 
 int /*<<< orphan*/  DELTA_HEIGHT_ALIGNMENT ; 
 int /*<<< orphan*/  DELTA_WIDTH_ALIGNMENT ; 
 void* V4L2_COLORSPACE_REC709 ; 
 void* V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 void* V4L2_QUANTIZATION_DEFAULT ; 
 void* V4L2_XFER_FUNC_DEFAULT ; 
 void* V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  estimated_au_size (void*,void*) ; 
 int /*<<< orphan*/  frame_size (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct delta_streaminfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_default_params(struct delta_ctx *ctx)
{
	struct delta_frameinfo *frameinfo = &ctx->frameinfo;
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;

	memset(frameinfo, 0, sizeof(*frameinfo));
	frameinfo->pixelformat = V4L2_PIX_FMT_NV12;
	frameinfo->width = DELTA_DEFAULT_WIDTH;
	frameinfo->height = DELTA_DEFAULT_HEIGHT;
	frameinfo->aligned_width = ALIGN(frameinfo->width,
					 DELTA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(frameinfo->height,
					  DELTA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelformat);
	frameinfo->field = V4L2_FIELD_NONE;
	frameinfo->colorspace = V4L2_COLORSPACE_REC709;
	frameinfo->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	frameinfo->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	frameinfo->quantization = V4L2_QUANTIZATION_DEFAULT;

	memset(streaminfo, 0, sizeof(*streaminfo));
	streaminfo->streamformat = DELTA_DEFAULT_STREAMFORMAT;
	streaminfo->width = DELTA_DEFAULT_WIDTH;
	streaminfo->height = DELTA_DEFAULT_HEIGHT;
	streaminfo->field = V4L2_FIELD_NONE;
	streaminfo->colorspace = V4L2_COLORSPACE_REC709;
	streaminfo->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	streaminfo->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	streaminfo->quantization = V4L2_QUANTIZATION_DEFAULT;

	ctx->max_au_size = estimated_au_size(streaminfo->width,
					     streaminfo->height);
}
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
typedef  int u32 ;
struct vdoa_q_data {unsigned int width; unsigned int height; unsigned int bytesperline; unsigned int sizeimage; int pixelformat; } ;
struct vdoa_ctx {struct vdoa_q_data* q_data; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
#define  V4L2_PIX_FMT_NV12 129 
#define  V4L2_PIX_FMT_YUYV 128 
 unsigned int round_up (unsigned int,int) ; 

int vdoa_context_configure(struct vdoa_ctx *ctx,
			   unsigned int width, unsigned int height,
			   u32 pixelformat)
{
	struct vdoa_q_data *src_q_data;
	struct vdoa_q_data *dst_q_data;

	if (width < 16 || width  > 8192 || width % 16 != 0 ||
	    height < 16 || height > 4096 || height % 16 != 0)
		return -EINVAL;

	if (pixelformat != V4L2_PIX_FMT_YUYV &&
	    pixelformat != V4L2_PIX_FMT_NV12)
		return -EINVAL;

	/* If no context is passed, only check if the format is valid */
	if (!ctx)
		return 0;

	src_q_data = &ctx->q_data[V4L2_M2M_SRC];
	dst_q_data = &ctx->q_data[V4L2_M2M_DST];

	src_q_data->width = width;
	src_q_data->height = height;
	src_q_data->bytesperline = width;
	src_q_data->sizeimage =
		round_up(src_q_data->bytesperline * height, 4096) +
		src_q_data->bytesperline * height / 2;

	dst_q_data->width = width;
	dst_q_data->height = height;
	dst_q_data->pixelformat = pixelformat;
	switch (pixelformat) {
	case V4L2_PIX_FMT_YUYV:
		dst_q_data->bytesperline = width * 2;
		dst_q_data->sizeimage = dst_q_data->bytesperline * height;
		break;
	case V4L2_PIX_FMT_NV12:
	default:
		dst_q_data->bytesperline = width;
		dst_q_data->sizeimage =
			dst_q_data->bytesperline * height * 3 / 2;
		break;
	}

	return 0;
}
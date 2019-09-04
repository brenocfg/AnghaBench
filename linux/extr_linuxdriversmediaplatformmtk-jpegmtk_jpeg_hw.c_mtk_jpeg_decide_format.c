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
struct mtk_jpeg_dec_param {int src_color; int* sampling_w; int* sampling_h; int uv_brz_w; void* dst_fourcc; } ;

/* Variables and functions */
#define  MTK_JPEG_COLOR_400 134 
#define  MTK_JPEG_COLOR_420 133 
#define  MTK_JPEG_COLOR_422 132 
#define  MTK_JPEG_COLOR_422V 131 
#define  MTK_JPEG_COLOR_422VX2 130 
#define  MTK_JPEG_COLOR_422X2 129 
#define  MTK_JPEG_COLOR_444 128 
 void* V4L2_PIX_FMT_GREY ; 
 void* V4L2_PIX_FMT_YUV420M ; 
 void* V4L2_PIX_FMT_YUV422M ; 

__attribute__((used)) static int mtk_jpeg_decide_format(struct mtk_jpeg_dec_param *param)
{
	param->src_color = (param->sampling_w[0] << 20) |
			   (param->sampling_h[0] << 16) |
			   (param->sampling_w[1] << 12) |
			   (param->sampling_h[1] << 8) |
			   (param->sampling_w[2] << 4) |
			   (param->sampling_h[2]);

	param->uv_brz_w = 0;
	switch (param->src_color) {
	case MTK_JPEG_COLOR_444:
		param->uv_brz_w = 1;
		param->dst_fourcc = V4L2_PIX_FMT_YUV422M;
		break;
	case MTK_JPEG_COLOR_422X2:
	case MTK_JPEG_COLOR_422:
		param->dst_fourcc = V4L2_PIX_FMT_YUV422M;
		break;
	case MTK_JPEG_COLOR_422V:
	case MTK_JPEG_COLOR_422VX2:
		param->uv_brz_w = 1;
		param->dst_fourcc = V4L2_PIX_FMT_YUV420M;
		break;
	case MTK_JPEG_COLOR_420:
		param->dst_fourcc = V4L2_PIX_FMT_YUV420M;
		break;
	case MTK_JPEG_COLOR_400:
		param->dst_fourcc = V4L2_PIX_FMT_GREY;
		break;
	default:
		param->dst_fourcc = 0;
		return -1;
	}

	return 0;
}
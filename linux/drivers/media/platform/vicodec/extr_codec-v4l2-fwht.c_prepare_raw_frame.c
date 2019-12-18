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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_fwht_pixfmt_info {int id; int /*<<< orphan*/  components_num; int /*<<< orphan*/  chroma_step; int /*<<< orphan*/  luma_alpha_step; int /*<<< orphan*/  height_div; int /*<<< orphan*/  width_div; } ;
struct fwht_raw_frame {int /*<<< orphan*/ * luma; int /*<<< orphan*/ * cr; int /*<<< orphan*/ * cb; int /*<<< orphan*/ * alpha; int /*<<< orphan*/  components_num; int /*<<< orphan*/  chroma_step; int /*<<< orphan*/  luma_alpha_step; int /*<<< orphan*/  height_div; int /*<<< orphan*/  width_div; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_ABGR32 155 
#define  V4L2_PIX_FMT_ARGB32 154 
#define  V4L2_PIX_FMT_BGR24 153 
#define  V4L2_PIX_FMT_BGR32 152 
#define  V4L2_PIX_FMT_BGRA32 151 
#define  V4L2_PIX_FMT_BGRX32 150 
#define  V4L2_PIX_FMT_GREY 149 
#define  V4L2_PIX_FMT_HSV24 148 
#define  V4L2_PIX_FMT_HSV32 147 
#define  V4L2_PIX_FMT_NV12 146 
#define  V4L2_PIX_FMT_NV16 145 
#define  V4L2_PIX_FMT_NV21 144 
#define  V4L2_PIX_FMT_NV24 143 
#define  V4L2_PIX_FMT_NV42 142 
#define  V4L2_PIX_FMT_NV61 141 
#define  V4L2_PIX_FMT_RGB24 140 
#define  V4L2_PIX_FMT_RGB32 139 
#define  V4L2_PIX_FMT_RGBA32 138 
#define  V4L2_PIX_FMT_RGBX32 137 
#define  V4L2_PIX_FMT_UYVY 136 
#define  V4L2_PIX_FMT_VYUY 135 
#define  V4L2_PIX_FMT_XBGR32 134 
#define  V4L2_PIX_FMT_XRGB32 133 
#define  V4L2_PIX_FMT_YUV420 132 
#define  V4L2_PIX_FMT_YUV422P 131 
#define  V4L2_PIX_FMT_YUYV 130 
#define  V4L2_PIX_FMT_YVU420 129 
#define  V4L2_PIX_FMT_YVYU 128 

__attribute__((used)) static int prepare_raw_frame(struct fwht_raw_frame *rf,
			 const struct v4l2_fwht_pixfmt_info *info, u8 *buf,
			 unsigned int size)
{
	rf->luma = buf;
	rf->width_div = info->width_div;
	rf->height_div = info->height_div;
	rf->luma_alpha_step = info->luma_alpha_step;
	rf->chroma_step = info->chroma_step;
	rf->alpha = NULL;
	rf->components_num = info->components_num;

	/*
	 * The buffer is NULL if it is the reference
	 * frame of an I-frame in the stateless decoder
	 */
	if (!buf) {
		rf->luma = NULL;
		rf->cb = NULL;
		rf->cr = NULL;
		rf->alpha = NULL;
		return 0;
	}
	switch (info->id) {
	case V4L2_PIX_FMT_GREY:
		rf->cb = NULL;
		rf->cr = NULL;
		break;
	case V4L2_PIX_FMT_YUV420:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + size / 4;
		break;
	case V4L2_PIX_FMT_YVU420:
		rf->cr = rf->luma + size;
		rf->cb = rf->cr + size / 4;
		break;
	case V4L2_PIX_FMT_YUV422P:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + size / 2;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV24:
		rf->cb = rf->luma + size;
		rf->cr = rf->cb + 1;
		break;
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_NV42:
		rf->cr = rf->luma + size;
		rf->cb = rf->cr + 1;
		break;
	case V4L2_PIX_FMT_YUYV:
		rf->cb = rf->luma + 1;
		rf->cr = rf->cb + 2;
		break;
	case V4L2_PIX_FMT_YVYU:
		rf->cr = rf->luma + 1;
		rf->cb = rf->cr + 2;
		break;
	case V4L2_PIX_FMT_UYVY:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_VYUY:
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_RGB24:
	case V4L2_PIX_FMT_HSV24:
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_BGR24:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_XRGB32:
	case V4L2_PIX_FMT_HSV32:
		rf->cr = rf->luma + 1;
		rf->cb = rf->cr + 2;
		rf->luma += 2;
		break;
	case V4L2_PIX_FMT_BGR32:
	case V4L2_PIX_FMT_XBGR32:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_ARGB32:
		rf->alpha = rf->luma;
		rf->cr = rf->luma + 1;
		rf->cb = rf->cr + 2;
		rf->luma += 2;
		break;
	case V4L2_PIX_FMT_ABGR32:
		rf->cb = rf->luma;
		rf->cr = rf->cb + 2;
		rf->luma++;
		rf->alpha = rf->cr + 1;
		break;
	case V4L2_PIX_FMT_BGRX32:
		rf->cb = rf->luma + 1;
		rf->cr = rf->cb + 2;
		rf->luma += 2;
		break;
	case V4L2_PIX_FMT_BGRA32:
		rf->alpha = rf->luma;
		rf->cb = rf->luma + 1;
		rf->cr = rf->cb + 2;
		rf->luma += 2;
		break;
	case V4L2_PIX_FMT_RGBX32:
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		break;
	case V4L2_PIX_FMT_RGBA32:
		rf->alpha = rf->luma + 3;
		rf->cr = rf->luma;
		rf->cb = rf->cr + 2;
		rf->luma++;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
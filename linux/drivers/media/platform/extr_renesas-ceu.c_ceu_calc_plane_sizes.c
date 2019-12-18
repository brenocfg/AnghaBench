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
struct v4l2_pix_format_mplane {int pixelformat; int num_planes; int width; unsigned int height; int /*<<< orphan*/ * plane_fmt; } ;
struct ceu_fmt {int bpp; } ;
struct ceu_device {int dummy; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 135 
#define  V4L2_PIX_FMT_NV16 134 
#define  V4L2_PIX_FMT_NV21 133 
#define  V4L2_PIX_FMT_NV61 132 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_VYUY 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  ceu_update_plane_sizes (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static void ceu_calc_plane_sizes(struct ceu_device *ceudev,
				 const struct ceu_fmt *ceu_fmt,
				 struct v4l2_pix_format_mplane *pix)
{
	unsigned int bpl, szimage;

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_VYUY:
		pix->num_planes	= 1;
		bpl		= pix->width * ceu_fmt->bpp / 8;
		szimage		= pix->height * bpl;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		break;

	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		pix->num_planes	= 2;
		bpl		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		ceu_update_plane_sizes(&pix->plane_fmt[1], bpl, szimage / 2);
		break;

	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
	default:
		pix->num_planes	= 2;
		bpl		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		ceu_update_plane_sizes(&pix->plane_fmt[1], bpl, szimage);
		break;
	}
}
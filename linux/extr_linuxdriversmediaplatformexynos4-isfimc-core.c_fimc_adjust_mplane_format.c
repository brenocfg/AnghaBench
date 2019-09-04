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
struct v4l2_plane_pix_format {int bytesperline; int /*<<< orphan*/  sizeimage; } ;
struct v4l2_pix_format_mplane {int num_planes; int height; int width; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct fimc_fmt {int memplanes; int colplanes; int* depth; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 
 scalar_t__ tiled_fmt (struct fimc_fmt*) ; 

void fimc_adjust_mplane_format(struct fimc_fmt *fmt, u32 width, u32 height,
			       struct v4l2_pix_format_mplane *pix)
{
	u32 bytesperline = 0;
	int i;

	pix->colorspace	= V4L2_COLORSPACE_JPEG;
	pix->field = V4L2_FIELD_NONE;
	pix->num_planes = fmt->memplanes;
	pix->pixelformat = fmt->fourcc;
	pix->height = height;
	pix->width = width;

	for (i = 0; i < pix->num_planes; ++i) {
		struct v4l2_plane_pix_format *plane_fmt = &pix->plane_fmt[i];
		u32 bpl = plane_fmt->bytesperline;
		u32 sizeimage;

		if (fmt->colplanes > 1 && (bpl == 0 || bpl < pix->width))
			bpl = pix->width; /* Planar */

		if (fmt->colplanes == 1 && /* Packed */
		    (bpl == 0 || ((bpl * 8) / fmt->depth[i]) < pix->width))
			bpl = (pix->width * fmt->depth[0]) / 8;
		/*
		 * Currently bytesperline for each plane is same, except
		 * V4L2_PIX_FMT_YUV420M format. This calculation may need
		 * to be changed when other multi-planar formats are added
		 * to the fimc_formats[] array.
		 */
		if (i == 0)
			bytesperline = bpl;
		else if (i == 1 && fmt->memplanes == 3)
			bytesperline /= 2;

		plane_fmt->bytesperline = bytesperline;
		sizeimage = pix->width * pix->height * fmt->depth[i] / 8;

		/* Ensure full last row for tiled formats */
		if (tiled_fmt(fmt)) {
			/* 64 * 32 * plane_fmt->bytesperline / 64 */
			u32 row_size = plane_fmt->bytesperline * 32;

			sizeimage = roundup(sizeimage, row_size);
		}

		plane_fmt->sizeimage = max(sizeimage, plane_fmt->sizeimage);
	}
}
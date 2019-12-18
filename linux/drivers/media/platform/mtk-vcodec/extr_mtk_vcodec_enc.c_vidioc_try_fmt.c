#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {int num_planes; int height; int width; int /*<<< orphan*/  reserved; scalar_t__ flags; TYPE_2__* plane_fmt; int /*<<< orphan*/  field; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct mtk_video_fmt {int num_planes; } ;
struct TYPE_4__ {int bytesperline; int sizeimage; int /*<<< orphan*/ * reserved; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int MTK_VENC_MAX_H ; 
 int MTK_VENC_MAX_W ; 
 int /*<<< orphan*/  MTK_VENC_MIN_H ; 
 int /*<<< orphan*/  MTK_VENC_MIN_W ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 void* clamp (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int vidioc_try_fmt(struct v4l2_format *f,
			  const struct mtk_video_fmt *fmt)
{
	struct v4l2_pix_format_mplane *pix_fmt_mp = &f->fmt.pix_mp;
	int i;

	pix_fmt_mp->field = V4L2_FIELD_NONE;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		pix_fmt_mp->num_planes = 1;
		pix_fmt_mp->plane_fmt[0].bytesperline = 0;
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		int tmp_w, tmp_h;

		pix_fmt_mp->height = clamp(pix_fmt_mp->height,
					MTK_VENC_MIN_H,
					MTK_VENC_MAX_H);
		pix_fmt_mp->width = clamp(pix_fmt_mp->width,
					MTK_VENC_MIN_W,
					MTK_VENC_MAX_W);

		/* find next closer width align 16, heign align 32, size align
		 * 64 rectangle
		 */
		tmp_w = pix_fmt_mp->width;
		tmp_h = pix_fmt_mp->height;
		v4l_bound_align_image(&pix_fmt_mp->width,
					MTK_VENC_MIN_W,
					MTK_VENC_MAX_W, 4,
					&pix_fmt_mp->height,
					MTK_VENC_MIN_H,
					MTK_VENC_MAX_H, 5, 6);

		if (pix_fmt_mp->width < tmp_w &&
			(pix_fmt_mp->width + 16) <= MTK_VENC_MAX_W)
			pix_fmt_mp->width += 16;
		if (pix_fmt_mp->height < tmp_h &&
			(pix_fmt_mp->height + 32) <= MTK_VENC_MAX_H)
			pix_fmt_mp->height += 32;

		mtk_v4l2_debug(0,
			"before resize width=%d, height=%d, after resize width=%d, height=%d, sizeimage=%d %d",
			tmp_w, tmp_h, pix_fmt_mp->width,
			pix_fmt_mp->height,
			pix_fmt_mp->plane_fmt[0].sizeimage,
			pix_fmt_mp->plane_fmt[1].sizeimage);

		pix_fmt_mp->num_planes = fmt->num_planes;
		pix_fmt_mp->plane_fmt[0].sizeimage =
				pix_fmt_mp->width * pix_fmt_mp->height +
				((ALIGN(pix_fmt_mp->width, 16) * 2) * 16);
		pix_fmt_mp->plane_fmt[0].bytesperline = pix_fmt_mp->width;

		if (pix_fmt_mp->num_planes == 2) {
			pix_fmt_mp->plane_fmt[1].sizeimage =
				(pix_fmt_mp->width * pix_fmt_mp->height) / 2 +
				(ALIGN(pix_fmt_mp->width, 16) * 16);
			pix_fmt_mp->plane_fmt[2].sizeimage = 0;
			pix_fmt_mp->plane_fmt[1].bytesperline =
							pix_fmt_mp->width;
			pix_fmt_mp->plane_fmt[2].bytesperline = 0;
		} else if (pix_fmt_mp->num_planes == 3) {
			pix_fmt_mp->plane_fmt[1].sizeimage =
			pix_fmt_mp->plane_fmt[2].sizeimage =
				(pix_fmt_mp->width * pix_fmt_mp->height) / 4 +
				((ALIGN(pix_fmt_mp->width, 16) / 2) * 16);
			pix_fmt_mp->plane_fmt[1].bytesperline =
				pix_fmt_mp->plane_fmt[2].bytesperline =
				pix_fmt_mp->width / 2;
		}
	}

	for (i = 0; i < pix_fmt_mp->num_planes; i++)
		memset(&(pix_fmt_mp->plane_fmt[i].reserved[0]), 0x0,
			   sizeof(pix_fmt_mp->plane_fmt[0].reserved));

	pix_fmt_mp->flags = 0;
	memset(&pix_fmt_mp->reserved, 0x0,
		sizeof(pix_fmt_mp->reserved));

	return 0;
}
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
struct vpe_fmt {int types; scalar_t__ fourcc; TYPE_2__** vpdma_fmt; scalar_t__ coplanar; } ;
struct vpe_ctx {int /*<<< orphan*/  dev; } ;
struct v4l2_plane_pix_format {unsigned int bytesperline; int sizeimage; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {scalar_t__ pixelformat; scalar_t__ field; int width; int height; int num_planes; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  reserved; scalar_t__ colorspace; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_4__ {int depth; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  H_ALIGN ; 
 int /*<<< orphan*/  MAX_H ; 
 int /*<<< orphan*/  MAX_W ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  S_ALIGN ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 scalar_t__ V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_COLORSPACE_SRGB ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 scalar_t__ V4L2_PIX_FMT_BGR24 ; 
 scalar_t__ V4L2_PIX_FMT_BGR32 ; 
 scalar_t__ V4L2_PIX_FMT_RGB24 ; 
 scalar_t__ V4L2_PIX_FMT_RGB32 ; 
 int VPDMA_DESC_ALIGN ; 
 int /*<<< orphan*/  VPDMA_STRIDE_ALIGN ; 
 size_t VPE_CHROMA ; 
 size_t VPE_LUMA ; 
 unsigned int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int __vpe_try_fmt(struct vpe_ctx *ctx, struct v4l2_format *f,
		       struct vpe_fmt *fmt, int type)
{
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *plane_fmt;
	unsigned int w_align;
	int i, depth, depth_bytes, height;
	unsigned int stride = 0;

	if (!fmt || !(fmt->types & type)) {
		vpe_err(ctx->dev, "Fourcc format (0x%08x) invalid.\n",
			pix->pixelformat);
		return -EINVAL;
	}

	if (pix->field != V4L2_FIELD_NONE && pix->field != V4L2_FIELD_ALTERNATE
			&& pix->field != V4L2_FIELD_SEQ_TB)
		pix->field = V4L2_FIELD_NONE;

	depth = fmt->vpdma_fmt[VPE_LUMA]->depth;

	/*
	 * the line stride should 16 byte aligned for VPDMA to work, based on
	 * the bytes per pixel, figure out how much the width should be aligned
	 * to make sure line stride is 16 byte aligned
	 */
	depth_bytes = depth >> 3;

	if (depth_bytes == 3) {
		/*
		 * if bpp is 3(as in some RGB formats), the pixel width doesn't
		 * really help in ensuring line stride is 16 byte aligned
		 */
		w_align = 4;
	} else {
		/*
		 * for the remainder bpp(4, 2 and 1), the pixel width alignment
		 * can ensure a line stride alignment of 16 bytes. For example,
		 * if bpp is 2, then the line stride can be 16 byte aligned if
		 * the width is 8 byte aligned
		 */

		/*
		 * HACK: using order_base_2() here causes lots of asm output
		 * errors with smatch, on i386:
		 * ./arch/x86/include/asm/bitops.h:457:22:
		 *		 warning: asm output is not an lvalue
		 * Perhaps some gcc optimization is doing the wrong thing
		 * there.
		 * Let's get rid of them by doing the calculus on two steps
		 */
		w_align = roundup_pow_of_two(VPDMA_DESC_ALIGN / depth_bytes);
		w_align = ilog2(w_align);
	}

	v4l_bound_align_image(&pix->width, MIN_W, MAX_W, w_align,
			      &pix->height, MIN_H, MAX_H, H_ALIGN,
			      S_ALIGN);

	if (!pix->num_planes)
		pix->num_planes = fmt->coplanar ? 2 : 1;
	else if (pix->num_planes > 1 && !fmt->coplanar)
		pix->num_planes = 1;

	pix->pixelformat = fmt->fourcc;

	/*
	 * For the actual image parameters, we need to consider the field
	 * height of the image for SEQ_TB buffers.
	 */
	if (pix->field == V4L2_FIELD_SEQ_TB)
		height = pix->height / 2;
	else
		height = pix->height;

	if (!pix->colorspace) {
		if (fmt->fourcc == V4L2_PIX_FMT_RGB24 ||
				fmt->fourcc == V4L2_PIX_FMT_BGR24 ||
				fmt->fourcc == V4L2_PIX_FMT_RGB32 ||
				fmt->fourcc == V4L2_PIX_FMT_BGR32) {
			pix->colorspace = V4L2_COLORSPACE_SRGB;
		} else {
			if (height > 1280)	/* HD */
				pix->colorspace = V4L2_COLORSPACE_REC709;
			else			/* SD */
				pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
		}
	}

	memset(pix->reserved, 0, sizeof(pix->reserved));
	for (i = 0; i < pix->num_planes; i++) {
		plane_fmt = &pix->plane_fmt[i];
		depth = fmt->vpdma_fmt[i]->depth;

		stride = (pix->width * fmt->vpdma_fmt[VPE_LUMA]->depth) >> 3;
		if (stride > plane_fmt->bytesperline)
			plane_fmt->bytesperline = stride;

		plane_fmt->bytesperline = ALIGN(plane_fmt->bytesperline,
						VPDMA_STRIDE_ALIGN);

		if (i == VPE_LUMA) {
			plane_fmt->sizeimage = pix->height *
					       plane_fmt->bytesperline;

			if (pix->num_planes == 1 && fmt->coplanar)
				plane_fmt->sizeimage += pix->height *
					plane_fmt->bytesperline *
					fmt->vpdma_fmt[VPE_CHROMA]->depth >> 3;

		} else { /* i == VIP_CHROMA */
			plane_fmt->sizeimage = (pix->height *
					       plane_fmt->bytesperline *
					       depth) >> 3;
		}
		memset(plane_fmt->reserved, 0, sizeof(plane_fmt->reserved));
	}

	return 0;
}
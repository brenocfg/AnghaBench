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
struct v4l2_pix_format_mplane {scalar_t__ field; scalar_t__ colorspace; void* height; void* width; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  pixelformat; } ;
struct fdp1_fmt {int types; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  fourcc; } ;
struct fdp1_ctx {int dummy; } ;

/* Variables and functions */
 int FDP1_MAX_H ; 
 int FDP1_MAX_W ; 
 int FDP1_MIN_H ; 
 int FDP1_MIN_W ; 
 int FDP1_OUTPUT ; 
 scalar_t__ V4L2_COLORSPACE_DEFAULT ; 
 scalar_t__ V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_FIELD_HAS_BOTH (scalar_t__) ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 void* clamp (unsigned int,int,int) ; 
 int /*<<< orphan*/  fdp1_compute_stride (struct v4l2_pix_format_mplane*,struct fdp1_fmt const*) ; 
 struct fdp1_fmt* fdp1_find_format (int /*<<< orphan*/ ) ; 
 unsigned int round_down (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_try_fmt_output(struct fdp1_ctx *ctx,
				const struct fdp1_fmt **fmtinfo,
				struct v4l2_pix_format_mplane *pix)
{
	const struct fdp1_fmt *fmt;
	unsigned int width;
	unsigned int height;

	/* Validate the pixel format to ensure the output queue supports it. */
	fmt = fdp1_find_format(pix->pixelformat);
	if (!fmt || !(fmt->types & FDP1_OUTPUT))
		fmt = fdp1_find_format(V4L2_PIX_FMT_YUYV);

	if (fmtinfo)
		*fmtinfo = fmt;

	pix->pixelformat = fmt->fourcc;
	pix->num_planes = fmt->num_planes;

	/*
	 * Progressive video and all interlaced field orders are acceptable.
	 * Default to V4L2_FIELD_INTERLACED.
	 */
	if (pix->field != V4L2_FIELD_NONE &&
	    pix->field != V4L2_FIELD_ALTERNATE &&
	    !V4L2_FIELD_HAS_BOTH(pix->field))
		pix->field = V4L2_FIELD_INTERLACED;

	/*
	 * The deinterlacer doesn't care about the colorspace, accept all values
	 * and default to V4L2_COLORSPACE_SMPTE170M. The YUV to RGB conversion
	 * at the output of the deinterlacer supports a subset of encodings and
	 * quantization methods and will only be available when the colorspace
	 * allows it.
	 */
	if (pix->colorspace == V4L2_COLORSPACE_DEFAULT)
		pix->colorspace = V4L2_COLORSPACE_SMPTE170M;

	/*
	 * Align the width and height for YUV 4:2:2 and 4:2:0 formats and clamp
	 * them to the supported frame size range. The height boundary are
	 * related to the full frame, divide them by two when the format passes
	 * fields in separate buffers.
	 */
	width = round_down(pix->width, fmt->hsub);
	pix->width = clamp(width, FDP1_MIN_W, FDP1_MAX_W);

	height = round_down(pix->height, fmt->vsub);
	if (pix->field == V4L2_FIELD_ALTERNATE)
		pix->height = clamp(height, FDP1_MIN_H / 2, FDP1_MAX_H / 2);
	else
		pix->height = clamp(height, FDP1_MIN_H, FDP1_MAX_H);

	fdp1_compute_stride(pix, fmt);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {unsigned int num_planes; unsigned int width; unsigned int height; TYPE_1__* plane_fmt; int /*<<< orphan*/  reserved; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  field; } ;
struct sun4i_csi_format {unsigned int num_planes; int hsub; int vsub; unsigned int* bpp; int /*<<< orphan*/  fourcc; } ;
struct sun4i_csi {int dummy; } ;
struct TYPE_2__ {unsigned int bytesperline; unsigned int sizeimage; int /*<<< orphan*/  reserved; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  CSI_MAX_HEIGHT ; 
 int /*<<< orphan*/  CSI_MAX_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_MAP_QUANTIZATION_DEFAULT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 void* clamp (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sun4i_csi_format* sun4i_csi_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sun4i_csi_format* sun4i_csi_formats ; 

__attribute__((used)) static void _sun4i_csi_try_fmt(struct sun4i_csi *csi,
			       struct v4l2_pix_format_mplane *pix)
{
	const struct sun4i_csi_format *_fmt;
	unsigned int height, width;
	unsigned int i;

	_fmt = sun4i_csi_find_format(&pix->pixelformat, NULL);
	if (!_fmt)
		_fmt = &sun4i_csi_formats[0];

	pix->field = V4L2_FIELD_NONE;
	pix->colorspace = V4L2_COLORSPACE_SRGB;
	pix->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(pix->colorspace);
	pix->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(pix->colorspace);
	pix->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true, pix->colorspace,
							  pix->ycbcr_enc);

	pix->num_planes = _fmt->num_planes;
	pix->pixelformat = _fmt->fourcc;

	memset(pix->reserved, 0, sizeof(pix->reserved));

	/* Align the width and height on the subsampling */
	width = ALIGN(pix->width, _fmt->hsub);
	height = ALIGN(pix->height, _fmt->vsub);

	/* Clamp the width and height to our capabilities */
	pix->width = clamp(width, _fmt->hsub, CSI_MAX_WIDTH);
	pix->height = clamp(height, _fmt->vsub, CSI_MAX_HEIGHT);

	for (i = 0; i < _fmt->num_planes; i++) {
		unsigned int hsub = i > 0 ? _fmt->hsub : 1;
		unsigned int vsub = i > 0 ? _fmt->vsub : 1;
		unsigned int bpl;

		bpl = pix->width / hsub * _fmt->bpp[i] / 8;
		pix->plane_fmt[i].bytesperline = bpl;
		pix->plane_fmt[i].sizeimage = bpl * pix->height / vsub;
		memset(pix->plane_fmt[i].reserved, 0,
		       sizeof(pix->plane_fmt[i].reserved));
	}
}
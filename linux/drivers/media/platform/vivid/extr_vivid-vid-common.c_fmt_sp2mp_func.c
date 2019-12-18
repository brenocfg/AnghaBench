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
struct v4l2_plane_pix_format {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; } ;
struct v4l2_pix_format_mplane {int /*<<< orphan*/  flags; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct v4l2_plane_pix_format* plane_fmt; } ;
struct v4l2_pix_format {int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
typedef  int (* fmtfunc ) (struct file*,void*,struct v4l2_format*) ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_sp2mp (struct v4l2_format*,struct v4l2_format*) ; 

int fmt_sp2mp_func(struct file *file, void *priv,
		struct v4l2_format *f, fmtfunc func)
{
	struct v4l2_format fmt;
	struct v4l2_pix_format_mplane *mp = &fmt.fmt.pix_mp;
	struct v4l2_plane_pix_format *ppix = &mp->plane_fmt[0];
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	/* Converts to a mplane format */
	fmt_sp2mp(f, &fmt);
	/* Passes it to the generic mplane format function */
	ret = func(file, priv, &fmt);
	/* Copies back the mplane data to the single plane format */
	pix->width = mp->width;
	pix->height = mp->height;
	pix->pixelformat = mp->pixelformat;
	pix->field = mp->field;
	pix->colorspace = mp->colorspace;
	pix->xfer_func = mp->xfer_func;
	/* Also copies hsv_enc */
	pix->ycbcr_enc = mp->ycbcr_enc;
	pix->quantization = mp->quantization;
	pix->sizeimage = ppix->sizeimage;
	pix->bytesperline = ppix->bytesperline;
	pix->flags = mp->flags;
	return ret;
}
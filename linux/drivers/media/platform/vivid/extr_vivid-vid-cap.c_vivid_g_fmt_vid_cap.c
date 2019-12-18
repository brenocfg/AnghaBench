#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int height; int /*<<< orphan*/  width; } ;
struct vivid_dev {TYPE_4__* fmt_cap; int /*<<< orphan*/  tpg; int /*<<< orphan*/  field_cap; TYPE_2__ fmt_cap_rect; } ;
struct v4l2_pix_format_mplane {int height; unsigned int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  hsv_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {scalar_t__ color_enc; unsigned int buffers; int* vdownsampling; scalar_t__* data_offset; int /*<<< orphan*/  fourcc; } ;
struct TYPE_7__ {scalar_t__ sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */
 scalar_t__ TGP_COLOR_ENC_HSV ; 
 int /*<<< orphan*/  tpg_g_bytesperline (int /*<<< orphan*/ *,unsigned int) ; 
 int tpg_g_line_width (int /*<<< orphan*/ *,unsigned int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_colorspace_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_hsv_enc_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_quantization_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_xfer_func_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_ycbcr_enc_cap (struct vivid_dev*) ; 

int vivid_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct v4l2_pix_format_mplane *mp = &f->fmt.pix_mp;
	unsigned p;

	mp->width        = dev->fmt_cap_rect.width;
	mp->height       = dev->fmt_cap_rect.height;
	mp->field        = dev->field_cap;
	mp->pixelformat  = dev->fmt_cap->fourcc;
	mp->colorspace   = vivid_colorspace_cap(dev);
	mp->xfer_func    = vivid_xfer_func_cap(dev);
	if (dev->fmt_cap->color_enc == TGP_COLOR_ENC_HSV)
		mp->hsv_enc    = vivid_hsv_enc_cap(dev);
	else
		mp->ycbcr_enc    = vivid_ycbcr_enc_cap(dev);
	mp->quantization = vivid_quantization_cap(dev);
	mp->num_planes = dev->fmt_cap->buffers;
	for (p = 0; p < mp->num_planes; p++) {
		mp->plane_fmt[p].bytesperline = tpg_g_bytesperline(&dev->tpg, p);
		mp->plane_fmt[p].sizeimage =
			(tpg_g_line_width(&dev->tpg, p) * mp->height) /
			dev->fmt_cap->vdownsampling[p] +
			dev->fmt_cap->data_offset[p];
	}
	return 0;
}
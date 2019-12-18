#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vivid_fmt {unsigned int buffers; unsigned int planes; unsigned int* vdownsampling; scalar_t__* data_offset; int /*<<< orphan*/  fourcc; } ;
struct TYPE_5__ {int height; int /*<<< orphan*/  width; } ;
struct vivid_dev {unsigned int* bytesperline_out; int /*<<< orphan*/  quantization_out; int /*<<< orphan*/  ycbcr_enc_out; int /*<<< orphan*/  xfer_func_out; int /*<<< orphan*/  colorspace_out; int /*<<< orphan*/  field_out; TYPE_2__ fmt_out_rect; struct vivid_fmt* fmt_out; } ;
struct v4l2_pix_format_mplane {int height; unsigned int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_6__ {unsigned int bytesperline; scalar_t__ sizeimage; } ;

/* Variables and functions */
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_g_fmt_vid_out(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct v4l2_pix_format_mplane *mp = &f->fmt.pix_mp;
	const struct vivid_fmt *fmt = dev->fmt_out;
	unsigned p;

	mp->width        = dev->fmt_out_rect.width;
	mp->height       = dev->fmt_out_rect.height;
	mp->field        = dev->field_out;
	mp->pixelformat  = fmt->fourcc;
	mp->colorspace   = dev->colorspace_out;
	mp->xfer_func    = dev->xfer_func_out;
	mp->ycbcr_enc    = dev->ycbcr_enc_out;
	mp->quantization = dev->quantization_out;
	mp->num_planes = fmt->buffers;
	for (p = 0; p < mp->num_planes; p++) {
		mp->plane_fmt[p].bytesperline = dev->bytesperline_out[p];
		mp->plane_fmt[p].sizeimage =
			mp->plane_fmt[p].bytesperline * mp->height +
			fmt->data_offset[p];
	}
	for (p = fmt->buffers; p < fmt->planes; p++) {
		unsigned stride = dev->bytesperline_out[p];

		mp->plane_fmt[0].sizeimage +=
			(stride * mp->height) / fmt->vdownsampling[p];
	}
	return 0;
}
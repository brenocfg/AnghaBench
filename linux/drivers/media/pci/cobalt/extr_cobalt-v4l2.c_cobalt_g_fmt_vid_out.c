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
struct v4l2_pix_format {int height; int bytesperline; int sizeimage; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int height; int stride; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_fmt_vid_out(struct file *file, void *priv_fh,
		struct v4l2_format *f)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytesperline = s->stride;
	pix->field = V4L2_FIELD_NONE;
	pix->pixelformat = s->pixfmt;
	pix->colorspace = s->colorspace;
	pix->xfer_func = s->xfer_func;
	pix->ycbcr_enc = s->ycbcr_enc;
	pix->quantization = s->quantization;
	pix->sizeimage = pix->bytesperline * pix->height;

	return 0;
}
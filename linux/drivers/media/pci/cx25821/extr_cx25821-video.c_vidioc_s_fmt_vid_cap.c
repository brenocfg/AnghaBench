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
struct TYPE_3__ {scalar_t__ pixelformat; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct cx25821_dev {int dummy; } ;
struct cx25821_channel {int width; int use_cif_resolution; int cif_width; int /*<<< orphan*/  height; int /*<<< orphan*/  field; int /*<<< orphan*/  fmt; struct cx25821_dev* dev; } ;

/* Variables and functions */
 int PIXEL_FRMT_411 ; 
 int PIXEL_FRMT_422 ; 
 int /*<<< orphan*/  SRAM_CH00 ; 
 scalar_t__ V4L2_PIX_FMT_Y41P ; 
 int /*<<< orphan*/  cx25821_format_by_fourcc (scalar_t__) ; 
 int /*<<< orphan*/  cx25821_set_pixel_format (struct cx25821_dev*,int /*<<< orphan*/ ,int) ; 
 int cx25821_vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  medusa_set_resolution (struct cx25821_dev*,int,int /*<<< orphan*/ ) ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cx25821_channel *chan = video_drvdata(file);
	struct cx25821_dev *dev = chan->dev;
	int pix_format = PIXEL_FRMT_422;
	int err;

	err = cx25821_vidioc_try_fmt_vid_cap(file, priv, f);

	if (0 != err)
		return err;

	chan->fmt = cx25821_format_by_fourcc(f->fmt.pix.pixelformat);
	chan->field = f->fmt.pix.field;
	chan->width = f->fmt.pix.width;
	chan->height = f->fmt.pix.height;

	if (f->fmt.pix.pixelformat == V4L2_PIX_FMT_Y41P)
		pix_format = PIXEL_FRMT_411;
	else
		pix_format = PIXEL_FRMT_422;

	cx25821_set_pixel_format(dev, SRAM_CH00, pix_format);

	/* check if cif resolution */
	if (chan->width == 320 || chan->width == 352)
		chan->use_cif_resolution = 1;
	else
		chan->use_cif_resolution = 0;

	chan->cif_width = chan->width;
	medusa_set_resolution(dev, chan->width, SRAM_CH00);
	return 0;
}
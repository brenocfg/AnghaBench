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
struct TYPE_5__ {int offset; int sampling_rate; int* start; void** count; int /*<<< orphan*/  sample_format; int /*<<< orphan*/  samples_per_line; } ;
struct TYPE_6__ {TYPE_2__ vbi; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct cx8800_dev {TYPE_1__* core; } ;
struct TYPE_4__ {int tvnorm; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int V4L2_VBI_ITU_625_F1_START ; 
 int V4L2_VBI_ITU_625_F2_START ; 
 int /*<<< orphan*/  VBI_LINE_LENGTH ; 
 void* VBI_LINE_NTSC_COUNT ; 
 void* VBI_LINE_PAL_COUNT ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 

int cx8800_vbi_fmt(struct file *file, void *priv,
		   struct v4l2_format *f)
{
	struct cx8800_dev *dev = video_drvdata(file);

	f->fmt.vbi.samples_per_line = VBI_LINE_LENGTH;
	f->fmt.vbi.sample_format = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 244;

	if (dev->core->tvnorm & V4L2_STD_525_60) {
		/* ntsc */
		f->fmt.vbi.sampling_rate = 28636363;
		f->fmt.vbi.start[0] = 10;
		f->fmt.vbi.start[1] = 273;
		f->fmt.vbi.count[0] = VBI_LINE_NTSC_COUNT;
		f->fmt.vbi.count[1] = VBI_LINE_NTSC_COUNT;

	} else if (dev->core->tvnorm & V4L2_STD_625_50) {
		/* pal */
		f->fmt.vbi.sampling_rate = 35468950;
		f->fmt.vbi.start[0] = V4L2_VBI_ITU_625_F1_START + 5;
		f->fmt.vbi.start[1] = V4L2_VBI_ITU_625_F2_START + 5;
		f->fmt.vbi.count[0] = VBI_LINE_PAL_COUNT;
		f->fmt.vbi.count[1] = VBI_LINE_PAL_COUNT;
	}
	return 0;
}
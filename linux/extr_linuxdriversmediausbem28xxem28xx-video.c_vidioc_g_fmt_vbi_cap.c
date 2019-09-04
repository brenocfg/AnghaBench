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
struct TYPE_3__ {int sampling_rate; int* start; int /*<<< orphan*/  reserved; int /*<<< orphan*/ * count; scalar_t__ flags; scalar_t__ offset; int /*<<< orphan*/  sample_format; int /*<<< orphan*/  samples_per_line; } ;
struct TYPE_4__ {TYPE_1__ vbi; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {int norm; int /*<<< orphan*/  vbi_height; int /*<<< orphan*/  vbi_width; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fmt_vbi_cap(struct file *file, void *priv,
				struct v4l2_format *format)
{
	struct em28xx         *dev  = video_drvdata(file);
	struct em28xx_v4l2    *v4l2 = dev->v4l2;

	format->fmt.vbi.samples_per_line = v4l2->vbi_width;
	format->fmt.vbi.sample_format = V4L2_PIX_FMT_GREY;
	format->fmt.vbi.offset = 0;
	format->fmt.vbi.flags = 0;
	format->fmt.vbi.sampling_rate = 6750000 * 4 / 2;
	format->fmt.vbi.count[0] = v4l2->vbi_height;
	format->fmt.vbi.count[1] = v4l2->vbi_height;
	memset(format->fmt.vbi.reserved, 0, sizeof(format->fmt.vbi.reserved));

	/* Varies by video standard (NTSC, PAL, etc.) */
	if (v4l2->norm & V4L2_STD_525_60) {
		/* NTSC */
		format->fmt.vbi.start[0] = 10;
		format->fmt.vbi.start[1] = 273;
	} else if (v4l2->norm & V4L2_STD_625_50) {
		/* PAL */
		format->fmt.vbi.start[0] = 6;
		format->fmt.vbi.start[1] = 318;
	}

	return 0;
}
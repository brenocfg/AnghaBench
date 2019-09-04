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
struct v4l2_fmtdesc {int index; int pixelformat; int* description; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int nmodes; TYPE_1__* cam_mode; } ;
struct gspca_dev {TYPE_2__ cam; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_3__ {scalar_t__ pixelformat; int sizeimage; int width; int height; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 struct gspca_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
				struct v4l2_fmtdesc *fmtdesc)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);
	int i, j, index;
	__u32 fmt_tb[8];

	/* give an index to each format */
	index = 0;
	for (i = gspca_dev->cam.nmodes; --i >= 0; ) {
		fmt_tb[index] = gspca_dev->cam.cam_mode[i].pixelformat;
		j = 0;
		for (;;) {
			if (fmt_tb[j] == fmt_tb[index])
				break;
			j++;
		}
		if (j == index) {
			if (fmtdesc->index == index)
				break;		/* new format */
			index++;
			if (index >= ARRAY_SIZE(fmt_tb))
				return -EINVAL;
		}
	}
	if (i < 0)
		return -EINVAL;		/* no more format */

	fmtdesc->pixelformat = fmt_tb[index];
	if (gspca_dev->cam.cam_mode[i].sizeimage <
			gspca_dev->cam.cam_mode[i].width *
				gspca_dev->cam.cam_mode[i].height)
		fmtdesc->flags = V4L2_FMT_FLAG_COMPRESSED;
	fmtdesc->description[0] = fmtdesc->pixelformat & 0xff;
	fmtdesc->description[1] = (fmtdesc->pixelformat >> 8) & 0xff;
	fmtdesc->description[2] = (fmtdesc->pixelformat >> 16) & 0xff;
	fmtdesc->description[3] = fmtdesc->pixelformat >> 24;
	fmtdesc->description[4] = '\0';
	return 0;
}
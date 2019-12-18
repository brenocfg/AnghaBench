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
struct TYPE_5__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct s2255_vc {int std; int width; int height; TYPE_1__* fmt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int depth; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int NUM_LINES_1CIFS_NTSC ; 
 int NUM_LINES_1CIFS_PAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_TOP ; 
 int V4L2_STD_525_60 ; 
 struct s2255_vc* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fmt_vid_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct s2255_vc *vc = video_drvdata(file);
	int is_ntsc = vc->std & V4L2_STD_525_60;

	f->fmt.pix.width = vc->width;
	f->fmt.pix.height = vc->height;
	if (f->fmt.pix.height >=
	    (is_ntsc ? NUM_LINES_1CIFS_NTSC : NUM_LINES_1CIFS_PAL) * 2)
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	else
		f->fmt.pix.field = V4L2_FIELD_TOP;
	f->fmt.pix.pixelformat = vc->fmt->fourcc;
	f->fmt.pix.bytesperline = f->fmt.pix.width * (vc->fmt->depth >> 3);
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}
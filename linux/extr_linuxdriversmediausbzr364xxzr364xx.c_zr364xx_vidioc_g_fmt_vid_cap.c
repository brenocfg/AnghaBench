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
struct zr364xx_camera {int width; int height; } ;
struct TYPE_4__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_3__* formats ; 
 struct zr364xx_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int zr364xx_vidioc_g_fmt_vid_cap(struct file *file, void *priv,
				    struct v4l2_format *f)
{
	struct zr364xx_camera *cam;

	if (!file)
		return -ENODEV;
	cam = video_drvdata(file);

	f->fmt.pix.pixelformat = formats[0].fourcc;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.width = cam->width;
	f->fmt.pix.height = cam->height;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	return 0;
}
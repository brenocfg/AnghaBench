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
struct TYPE_3__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct camera_data {int /*<<< orphan*/  frame_size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_g_fmt_vid_cap(struct file *file, void *fh,
					struct v4l2_format *f)
{
	struct camera_data *cam = video_drvdata(file);

	f->fmt.pix.width = cam->width;
	f->fmt.pix.height = cam->height;
	f->fmt.pix.pixelformat = cam->pixelformat;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = cam->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;

	return 0;
}
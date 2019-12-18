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
struct vpbe_layer {struct vpbe_display* disp_dev; } ;
struct vpbe_display {struct vpbe_device* vpbe_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_pix_format {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 
 int vpbe_try_format (struct vpbe_display*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_display_try_fmt(struct file *file, void *priv,
				  struct v4l2_format *fmt)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_display *disp_dev = layer->disp_dev;
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_TRY_FMT\n");

	if (V4L2_BUF_TYPE_VIDEO_OUTPUT != fmt->type) {
		v4l2_err(&vpbe_dev->v4l2_dev, "invalid type\n");
		return -EINVAL;
	}

	/* Check for valid field format */
	return  vpbe_try_format(disp_dev, pixfmt, 0);

}
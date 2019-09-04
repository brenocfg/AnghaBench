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
struct video_device {int dummy; } ;
struct v4l2_pix_format {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct common_obj {struct v4l2_format fmt; int /*<<< orphan*/  buffer_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 int EBUSY ; 
 size_t VPIF_VIDEO_INDEX ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int vpif_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vpif_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;
	int ret;

	if (vb2_is_busy(&common->buffer_queue))
		return -EBUSY;

	ret = vpif_try_fmt_vid_out(file, priv, fmt);
	if (ret)
		return ret;

	/* store the pix format in the channel object */
	common->fmt.fmt.pix = *pixfmt;

	/* store the format in the channel object */
	common->fmt = *fmt;
	return 0;
}
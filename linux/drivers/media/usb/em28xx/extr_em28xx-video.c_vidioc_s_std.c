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
typedef  scalar_t__ v4l2_std_id ;
struct TYPE_3__ {int width; int height; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {scalar_t__ norm; scalar_t__ streaming_users; int width; int height; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vscale; int /*<<< orphan*/  hscale; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ V4L2_STD_525_60 ; 
 int /*<<< orphan*/  em28xx_resolution_set (struct em28xx*) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  size_to_scale (struct em28xx*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  video ; 
 struct em28xx* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id norm)
{
	struct em28xx      *dev  = video_drvdata(file);
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	struct v4l2_format f;

	if (norm == v4l2->norm)
		return 0;

	if (v4l2->streaming_users > 0)
		return -EBUSY;

	v4l2->norm = norm;

	/* Adjusts width/height, if needed */
	f.fmt.pix.width = 720;
	f.fmt.pix.height = (norm & V4L2_STD_525_60) ? 480 : 576;
	vidioc_try_fmt_vid_cap(file, priv, &f);

	/* set new image size */
	v4l2->width = f.fmt.pix.width;
	v4l2->height = f.fmt.pix.height;
	size_to_scale(dev, v4l2->width, v4l2->height,
		      &v4l2->hscale, &v4l2->vscale);

	em28xx_resolution_set(dev);
	v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_std, v4l2->norm);

	return 0;
}
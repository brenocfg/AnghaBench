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
struct via_camera {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int viacam_do_try_fmt (struct via_camera*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_try_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_format *fmt)
{
	struct via_camera *cam = priv;
	struct v4l2_format sfmt;
	int ret;

	mutex_lock(&cam->lock);
	ret = viacam_do_try_fmt(cam, &fmt->fmt.pix, &sfmt.fmt.pix);
	mutex_unlock(&cam->lock);
	return ret;
}
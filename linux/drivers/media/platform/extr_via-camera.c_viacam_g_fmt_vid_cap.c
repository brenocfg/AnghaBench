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
struct via_camera {int /*<<< orphan*/  user_format; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct via_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int viacam_g_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_format *fmt)
{
	struct via_camera *cam = video_drvdata(filp);

	fmt->fmt.pix = cam->user_format;
	return 0;
}
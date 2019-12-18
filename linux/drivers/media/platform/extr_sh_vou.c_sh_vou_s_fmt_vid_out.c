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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct sh_vou_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int sh_vou_set_fmt_vid_out (struct sh_vou_device*,int /*<<< orphan*/ *) ; 
 int sh_vou_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);
	int ret = sh_vou_try_fmt_vid_out(file, priv, fmt);

	if (ret)
		return ret;
	return sh_vou_set_fmt_vid_out(vou_dev, &fmt->fmt.pix);
}
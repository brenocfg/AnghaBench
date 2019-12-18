#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  src_sd; int /*<<< orphan*/  src_sd_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int __capture_try_fmt_vid_cap (struct capture_priv*,struct v4l2_subdev_format*,struct v4l2_format*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_try_fmt_vid_cap(struct file *file, void *fh,
				   struct v4l2_format *f)
{
	struct capture_priv *priv = video_drvdata(file);
	struct v4l2_subdev_format fmt_src;
	int ret;

	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, NULL, &fmt_src);
	if (ret)
		return ret;

	return __capture_try_fmt_vid_cap(priv, &fmt_src, f, NULL, NULL);
}
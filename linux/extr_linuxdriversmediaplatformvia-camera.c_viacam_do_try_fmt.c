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
struct via_format {int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  pixelformat; } ;
struct via_camera {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct via_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,int /*<<< orphan*/ *) ; 
 struct via_format* via_find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viacam_fmt_post (struct v4l2_pix_format*,struct v4l2_pix_format*) ; 
 int /*<<< orphan*/  viacam_fmt_pre (struct v4l2_pix_format*,struct v4l2_pix_format*) ; 

__attribute__((used)) static int viacam_do_try_fmt(struct via_camera *cam,
		struct v4l2_pix_format *upix, struct v4l2_pix_format *spix)
{
	int ret;
	struct v4l2_subdev_pad_config pad_cfg;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	struct via_format *f = via_find_format(upix->pixelformat);

	upix->pixelformat = f->pixelformat;
	viacam_fmt_pre(upix, spix);
	v4l2_fill_mbus_format(&format.format, spix, f->mbus_code);
	ret = sensor_call(cam, pad, set_fmt, &pad_cfg, &format);
	v4l2_fill_pix_format(spix, &format.format);
	viacam_fmt_post(upix, spix);
	return ret;
}
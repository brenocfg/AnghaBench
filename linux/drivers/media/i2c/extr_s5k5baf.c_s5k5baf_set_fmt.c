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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  field; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k5baf_pixfmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct s5k5baf {size_t pixfmt; int /*<<< orphan*/  lock; TYPE_1__ crop_source; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PAD_CIS ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k5baf_pixfmt* s5k5baf_formats ; 
 int /*<<< orphan*/  s5k5baf_try_cis_format (struct v4l2_mbus_framefmt*) ; 
 size_t s5k5baf_try_isp_format (struct v4l2_mbus_framefmt*) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int s5k5baf_set_fmt(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct v4l2_mbus_framefmt *mf = &fmt->format;
	struct s5k5baf *state = to_s5k5baf(sd);
	const struct s5k5baf_pixfmt *pixfmt;
	int ret = 0;

	mf->field = V4L2_FIELD_NONE;

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		*v4l2_subdev_get_try_format(sd, cfg, fmt->pad) = *mf;
		return 0;
	}

	if (fmt->pad == PAD_CIS) {
		s5k5baf_try_cis_format(mf);
		return 0;
	}

	mutex_lock(&state->lock);

	if (state->streaming) {
		mutex_unlock(&state->lock);
		return -EBUSY;
	}

	state->pixfmt = s5k5baf_try_isp_format(mf);
	pixfmt = &s5k5baf_formats[state->pixfmt];
	mf->code = pixfmt->code;
	mf->colorspace = pixfmt->colorspace;
	mf->width = state->crop_source.width;
	mf->height = state->crop_source.height;

	mutex_unlock(&state->lock);
	return ret;
}
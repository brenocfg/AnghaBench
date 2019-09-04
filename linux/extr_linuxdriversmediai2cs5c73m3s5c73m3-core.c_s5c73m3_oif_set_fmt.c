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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {scalar_t__ which; int pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct s5c73m3_frame_size {int dummy; } ;
struct s5c73m3 {int apply_fmt; int /*<<< orphan*/  lock; scalar_t__ streaming; int /*<<< orphan*/  mbus_code; struct s5c73m3_frame_size const** oif_pix_size; } ;

/* Variables and functions */
 int EBUSY ; 
#define  OIF_ISP_PAD 130 
#define  OIF_JPEG_PAD 129 
#define  OIF_SOURCE_PAD 128 
 size_t RES_ISP ; 
 size_t RES_JPEG ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  s5c73m3_oif_try_format (struct s5c73m3*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*,struct s5c73m3_frame_size const**) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int) ; 

__attribute__((used)) static int s5c73m3_oif_set_fmt(struct v4l2_subdev *sd,
			 struct v4l2_subdev_pad_config *cfg,
			 struct v4l2_subdev_format *fmt)
{
	const struct s5c73m3_frame_size *frame_size = NULL;
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	struct v4l2_mbus_framefmt *mf;
	int ret = 0;

	mutex_lock(&state->lock);

	s5c73m3_oif_try_format(state, cfg, fmt, &frame_size);

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		mf = v4l2_subdev_get_try_format(sd, cfg, fmt->pad);
		*mf = fmt->format;
		if (fmt->pad == OIF_ISP_PAD) {
			mf = v4l2_subdev_get_try_format(sd, cfg, OIF_SOURCE_PAD);
			mf->width = fmt->format.width;
			mf->height = fmt->format.height;
		}
	} else {
		switch (fmt->pad) {
		case OIF_ISP_PAD:
			state->oif_pix_size[RES_ISP] = frame_size;
			break;
		case OIF_JPEG_PAD:
			state->oif_pix_size[RES_JPEG] = frame_size;
			break;
		case OIF_SOURCE_PAD:
			state->mbus_code = fmt->format.code;
			break;
		default:
			ret = -EBUSY;
		}

		if (state->streaming)
			ret = -EBUSY;
		else
			state->apply_fmt = 1;
	}

	mutex_unlock(&state->lock);

	return ret;
}
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
struct v4l2_subdev_selection {int target; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct smiapp_subdev {int /*<<< orphan*/  source_pad; } ;
struct smiapp_sensor {int /*<<< orphan*/ * limits; struct smiapp_subdev* scaler; struct smiapp_subdev* binner; struct smiapp_subdev* pixel_array; struct smiapp_subdev* src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMIAPP_DIGITAL_CROP_CAPABILITY_INPUT_CROP ; 
 size_t SMIAPP_LIMIT_DIGITAL_CROP_CAPABILITY ; 
 size_t SMIAPP_LIMIT_SCALING_CAPABILITY ; 
 int /*<<< orphan*/  SMIAPP_PAD_SINK ; 
 int /*<<< orphan*/  SMIAPP_PAD_SRC ; 
 int /*<<< orphan*/  SMIAPP_PA_PAD_SRC ; 
 int /*<<< orphan*/  SMIAPP_SCALING_CAPABILITY_NONE ; 
#define  V4L2_SEL_TGT_COMPOSE 132 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_NATIVE_SIZE 128 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 
 struct smiapp_subdev* to_smiapp_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int __smiapp_sel_supported(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_selection *sel)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	struct smiapp_subdev *ssd = to_smiapp_subdev(subdev);

	/* We only implement crop in three places. */
	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (ssd == sensor->pixel_array
		    && sel->pad == SMIAPP_PA_PAD_SRC)
			return 0;
		if (ssd == sensor->src
		    && sel->pad == SMIAPP_PAD_SRC)
			return 0;
		if (ssd == sensor->scaler
		    && sel->pad == SMIAPP_PAD_SINK
		    && sensor->limits[SMIAPP_LIMIT_DIGITAL_CROP_CAPABILITY]
		    == SMIAPP_DIGITAL_CROP_CAPABILITY_INPUT_CROP)
			return 0;
		return -EINVAL;
	case V4L2_SEL_TGT_NATIVE_SIZE:
		if (ssd == sensor->pixel_array
		    && sel->pad == SMIAPP_PA_PAD_SRC)
			return 0;
		return -EINVAL;
	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (sel->pad == ssd->source_pad)
			return -EINVAL;
		if (ssd == sensor->binner)
			return 0;
		if (ssd == sensor->scaler
		    && sensor->limits[SMIAPP_LIMIT_SCALING_CAPABILITY]
		    != SMIAPP_SCALING_CAPABILITY_NONE)
			return 0;
		/* Fall through */
	default:
		return -EINVAL;
	}
}
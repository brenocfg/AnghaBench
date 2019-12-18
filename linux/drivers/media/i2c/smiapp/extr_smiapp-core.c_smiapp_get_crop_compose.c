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
struct TYPE_2__ {unsigned int num_pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct v4l2_rect {int dummy; } ;
struct smiapp_subdev {struct v4l2_rect compose; struct v4l2_rect* crop; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SMIAPP_PAD_SINK ; 
 int V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct smiapp_subdev* to_smiapp_subdev (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_compose (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static void smiapp_get_crop_compose(struct v4l2_subdev *subdev,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_rect **crops,
				    struct v4l2_rect **comps, int which)
{
	struct smiapp_subdev *ssd = to_smiapp_subdev(subdev);
	unsigned int i;

	if (which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		if (crops)
			for (i = 0; i < subdev->entity.num_pads; i++)
				crops[i] = &ssd->crop[i];
		if (comps)
			*comps = &ssd->compose;
	} else {
		if (crops) {
			for (i = 0; i < subdev->entity.num_pads; i++) {
				crops[i] = v4l2_subdev_get_try_crop(subdev, cfg, i);
				BUG_ON(!crops[i]);
			}
		}
		if (comps) {
			*comps = v4l2_subdev_get_try_compose(subdev, cfg,
							     SMIAPP_PAD_SINK);
			BUG_ON(!*comps);
		}
	}
}
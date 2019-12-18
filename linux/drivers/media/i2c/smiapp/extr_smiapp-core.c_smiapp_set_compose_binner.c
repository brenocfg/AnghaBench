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
struct TYPE_4__ {unsigned int width; unsigned int height; } ;
struct v4l2_subdev_selection {scalar_t__ which; TYPE_2__ r; int /*<<< orphan*/  flags; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int width; int height; } ;
struct smiapp_sensor {unsigned int nbinning_subtypes; unsigned int binning_vertical; unsigned int binning_horizontal; TYPE_1__* binning_subtypes; } ;
struct TYPE_3__ {int horizontal; int vertical; } ;

/* Variables and functions */
 size_t SMIAPP_PAD_SINK ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int scaling_goodness (struct v4l2_subdev*,int,unsigned int,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static void smiapp_set_compose_binner(struct v4l2_subdev *subdev,
				      struct v4l2_subdev_pad_config *cfg,
				      struct v4l2_subdev_selection *sel,
				      struct v4l2_rect **crops,
				      struct v4l2_rect *comp)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	unsigned int i;
	unsigned int binh = 1, binv = 1;
	int best = scaling_goodness(
		subdev,
		crops[SMIAPP_PAD_SINK]->width, sel->r.width,
		crops[SMIAPP_PAD_SINK]->height, sel->r.height, sel->flags);

	for (i = 0; i < sensor->nbinning_subtypes; i++) {
		int this = scaling_goodness(
			subdev,
			crops[SMIAPP_PAD_SINK]->width
			/ sensor->binning_subtypes[i].horizontal,
			sel->r.width,
			crops[SMIAPP_PAD_SINK]->height
			/ sensor->binning_subtypes[i].vertical,
			sel->r.height, sel->flags);

		if (this > best) {
			binh = sensor->binning_subtypes[i].horizontal;
			binv = sensor->binning_subtypes[i].vertical;
			best = this;
		}
	}
	if (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		sensor->binning_vertical = binv;
		sensor->binning_horizontal = binh;
	}

	sel->r.width = (crops[SMIAPP_PAD_SINK]->width / binh) & ~1;
	sel->r.height = (crops[SMIAPP_PAD_SINK]->height / binv) & ~1;
}
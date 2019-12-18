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
struct vimc_deb_pix_map {int dummy; } ;
struct vimc_deb_device {scalar_t__ src_code; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ code; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; int /*<<< orphan*/  pad; scalar_t__ index; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_SINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_WIDTH ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_WIDTH ; 
 struct vimc_deb_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct vimc_deb_pix_map* vimc_deb_pix_map_by_code (scalar_t__) ; 

__attribute__((used)) static int vimc_deb_enum_frame_size(struct v4l2_subdev *sd,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_frame_size_enum *fse)
{
	struct vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

	if (fse->index)
		return -EINVAL;

	if (IS_SINK(fse->pad)) {
		const struct vimc_deb_pix_map *vpix =
			vimc_deb_pix_map_by_code(fse->code);

		if (!vpix)
			return -EINVAL;
	} else if (fse->code != vdeb->src_code) {
		return -EINVAL;
	}

	fse->min_width = VIMC_FRAME_MIN_WIDTH;
	fse->max_width = VIMC_FRAME_MAX_WIDTH;
	fse->min_height = VIMC_FRAME_MIN_HEIGHT;
	fse->max_height = VIMC_FRAME_MAX_HEIGHT;

	return 0;
}
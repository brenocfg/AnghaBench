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
struct v4l2_subdev_frame_size_enum {int index; scalar_t__ code; int min_width; int min_height; int max_width; int max_height; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int width; int height; } ;
struct et8ek8_reglist {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ET8EK8_REGLIST_MODE ; 
 int INT_MAX ; 
 struct et8ek8_reglist** et8ek8_reglist_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et8ek8_reglist_to_mbus (struct et8ek8_reglist*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  meta_reglist ; 

__attribute__((used)) static int et8ek8_enum_frame_size(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	struct et8ek8_reglist **list =
			et8ek8_reglist_first(&meta_reglist);
	struct v4l2_mbus_framefmt format;
	int cmp_width = INT_MAX;
	int cmp_height = INT_MAX;
	int index = fse->index;

	for (; *list; list++) {
		if ((*list)->type != ET8EK8_REGLIST_MODE)
			continue;

		et8ek8_reglist_to_mbus(*list, &format);
		if (fse->code != format.code)
			continue;

		/* Assume that the modes are grouped by frame size. */
		if (format.width == cmp_width && format.height == cmp_height)
			continue;

		cmp_width = format.width;
		cmp_height = format.height;

		if (index-- == 0) {
			fse->min_width = format.width;
			fse->min_height = format.height;
			fse->max_width = format.width;
			fse->max_height = format.height;
			return 0;
		}
	}

	return -EINVAL;
}
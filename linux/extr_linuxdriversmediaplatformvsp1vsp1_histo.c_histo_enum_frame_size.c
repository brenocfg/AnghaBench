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
struct v4l2_subdev_frame_size_enum {scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HISTO_MAX_SIZE ; 
 int /*<<< orphan*/  HISTO_MIN_SIZE ; 
 scalar_t__ HISTO_PAD_SINK ; 
 int vsp1_subdev_enum_frame_size (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_frame_size_enum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histo_enum_frame_size(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->pad != HISTO_PAD_SINK)
		return -EINVAL;

	return vsp1_subdev_enum_frame_size(subdev, cfg, fse, HISTO_MIN_SIZE,
					   HISTO_MIN_SIZE, HISTO_MAX_SIZE,
					   HISTO_MAX_SIZE);
}
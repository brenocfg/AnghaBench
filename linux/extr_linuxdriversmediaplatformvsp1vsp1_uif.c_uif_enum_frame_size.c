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
struct v4l2_subdev_frame_size_enum {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIF_MAX_SIZE ; 
 int /*<<< orphan*/  UIF_MIN_SIZE ; 
 int vsp1_subdev_enum_frame_size (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_frame_size_enum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uif_enum_frame_size(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_frame_size_enum *fse)
{
	return vsp1_subdev_enum_frame_size(subdev, cfg, fse, UIF_MIN_SIZE,
					   UIF_MIN_SIZE, UIF_MAX_SIZE,
					   UIF_MAX_SIZE);
}
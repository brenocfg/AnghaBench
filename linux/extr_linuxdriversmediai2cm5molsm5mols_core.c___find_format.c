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
struct v4l2_mbus_framefmt {int dummy; } ;
struct m5mols_info {struct v4l2_mbus_framefmt* ffmt; int /*<<< orphan*/  sd; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;
typedef  enum m5mols_restype { ____Placeholder_m5mols_restype } m5mols_restype ;

/* Variables and functions */
 int V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *__find_format(struct m5mols_info *info,
				struct v4l2_subdev_pad_config *cfg,
				enum v4l2_subdev_format_whence which,
				enum m5mols_restype type)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return cfg ? v4l2_subdev_get_try_format(&info->sd, cfg, 0) : NULL;

	return &info->ffmt[type];
}
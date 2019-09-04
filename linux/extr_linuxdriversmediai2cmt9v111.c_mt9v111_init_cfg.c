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
struct v4l2_subdev_pad_config {int /*<<< orphan*/  try_fmt; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt9v111_def_fmt ; 

__attribute__((used)) static int mt9v111_init_cfg(struct v4l2_subdev *subdev,
			    struct v4l2_subdev_pad_config *cfg)
{
	cfg->try_fmt = mt9v111_def_fmt;

	return 0;
}
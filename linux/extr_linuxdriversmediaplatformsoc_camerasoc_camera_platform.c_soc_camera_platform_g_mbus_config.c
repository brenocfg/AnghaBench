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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_config {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct soc_camera_platform_info {int /*<<< orphan*/  mbus_type; int /*<<< orphan*/  mbus_param; } ;

/* Variables and functions */
 struct soc_camera_platform_info* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int soc_camera_platform_g_mbus_config(struct v4l2_subdev *sd,
					     struct v4l2_mbus_config *cfg)
{
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(sd);

	cfg->flags = p->mbus_param;
	cfg->type = p->mbus_type;

	return 0;
}
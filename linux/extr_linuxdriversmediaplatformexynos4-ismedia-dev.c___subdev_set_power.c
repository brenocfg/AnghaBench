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
struct TYPE_2__ {int use_count; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int ENXIO ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_power ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __subdev_set_power(struct v4l2_subdev *sd, int on)
{
	int *use_count;
	int ret;

	if (sd == NULL)
		return -ENXIO;

	use_count = &sd->entity.use_count;
	if (on && (*use_count)++ > 0)
		return 0;
	else if (!on && (*use_count == 0 || --(*use_count) > 0))
		return 0;
	ret = v4l2_subdev_call(sd, core, s_power, on);

	return ret != -ENOIOCTLCMD ? ret : 0;
}
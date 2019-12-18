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
struct v4l2_streamparm {int dummy; } ;
struct soc_camera_device {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int v4l2_s_parm_cap (int /*<<< orphan*/ ,struct v4l2_subdev*,struct v4l2_streamparm*) ; 

__attribute__((used)) static int default_s_parm(struct soc_camera_device *icd,
			  struct v4l2_streamparm *a)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);

	return v4l2_s_parm_cap(icd->vdev, sd, a);
}
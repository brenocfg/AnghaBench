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
struct v4l2_subdev {int dummy; } ;
struct soc_camera_platform_info {TYPE_2__* icd; } ;
struct TYPE_4__ {TYPE_1__* sdesc; int /*<<< orphan*/  control; } ;
struct TYPE_3__ {int /*<<< orphan*/  subdev_desc; } ;

/* Variables and functions */
 int soc_camera_set_power (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct soc_camera_platform_info* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int soc_camera_platform_s_power(struct v4l2_subdev *sd, int on)
{
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(sd);

	return soc_camera_set_power(p->icd->control, &p->icd->sdesc->subdev_desc, NULL, on);
}
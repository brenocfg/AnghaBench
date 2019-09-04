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
struct TYPE_2__ {scalar_t__ function; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;

/* Variables and functions */
 scalar_t__ MEDIA_ENT_F_CAM_SENSOR ; 

__attribute__((used)) static inline bool s5k5baf_is_cis_subdev(struct v4l2_subdev *sd)
{
	return sd->entity.function == MEDIA_ENT_F_CAM_SENSOR;
}
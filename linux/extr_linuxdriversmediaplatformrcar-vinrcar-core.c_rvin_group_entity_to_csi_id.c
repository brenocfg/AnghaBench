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
struct v4l2_subdev {int dummy; } ;
struct rvin_group {TYPE_1__* csi; } ;
struct media_entity {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* subdev; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int RVIN_CSI_MAX ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 

__attribute__((used)) static int rvin_group_entity_to_csi_id(struct rvin_group *group,
				       struct media_entity *entity)
{
	struct v4l2_subdev *sd;
	unsigned int i;

	sd = media_entity_to_v4l2_subdev(entity);

	for (i = 0; i < RVIN_CSI_MAX; i++)
		if (group->csi[i].subdev == sd)
			return i;

	return -ENODEV;
}
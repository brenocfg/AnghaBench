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
struct vfe_line {int id; } ;
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct vfe_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

void msm_vfe_get_vfe_line_id(struct media_entity *entity, enum vfe_line_id *id)
{
	struct v4l2_subdev *sd;
	struct vfe_line *line;

	sd = media_entity_to_v4l2_subdev(entity);
	line = v4l2_get_subdevdata(sd);

	*id = line->id;
}
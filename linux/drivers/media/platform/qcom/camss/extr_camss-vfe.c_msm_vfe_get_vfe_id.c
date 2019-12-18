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
typedef  int /*<<< orphan*/  u8 ;
struct vfe_line {int dummy; } ;
struct vfe_device {int /*<<< orphan*/  id; } ;
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct vfe_device* to_vfe (struct vfe_line*) ; 
 struct vfe_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

void msm_vfe_get_vfe_id(struct media_entity *entity, u8 *id)
{
	struct v4l2_subdev *sd;
	struct vfe_line *line;
	struct vfe_device *vfe;

	sd = media_entity_to_v4l2_subdev(entity);
	line = v4l2_get_subdevdata(sd);
	vfe = to_vfe(line);

	*id = vfe->id;
}
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
typedef  int u32 ;
struct media_entity {int dummy; } ;
struct video_device {struct media_entity entity; TYPE_1__* queue; } ;
struct v4l2_subdev {int grp_id; struct media_entity entity; } ;
struct media_pad {struct media_entity* entity; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 struct media_pad* imx_media_pipeline_pad (struct media_entity*,int,int,int) ; 
 scalar_t__ is_media_entity_v4l2_subdev (struct media_entity*) ; 
 scalar_t__ is_media_entity_v4l2_video_device (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct video_device* media_entity_to_video_device (struct media_entity*) ; 

__attribute__((used)) static struct media_entity *
find_pipeline_entity(struct media_entity *start, u32 grp_id,
		     enum v4l2_buf_type buftype, bool upstream)
{
	struct media_pad *pad = NULL;
	struct video_device *vfd;
	struct v4l2_subdev *sd;

	if (grp_id && is_media_entity_v4l2_subdev(start)) {
		sd = media_entity_to_v4l2_subdev(start);
		if (sd->grp_id & grp_id)
			return &sd->entity;
	} else if (buftype && is_media_entity_v4l2_video_device(start)) {
		vfd = media_entity_to_video_device(start);
		if (buftype == vfd->queue->type)
			return &vfd->entity;
	}

	pad = imx_media_pipeline_pad(start, grp_id, buftype, upstream);

	return pad ? pad->entity : NULL;
}
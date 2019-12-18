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
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;
struct csid_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct csid_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

void msm_csid_get_csid_id(struct media_entity *entity, u8 *id)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct csid_device *csid = v4l2_get_subdevdata(sd);

	*id = csid->id;
}
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
struct v4l2_subdev {int dummy; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  csid_id; } ;
struct csiphy_device {TYPE_1__ cfg; } ;
struct csid_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EBUSY ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_PAD_FL_SOURCE ; 
 scalar_t__ media_entity_remote_pad (struct media_pad const*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 void* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csiphy_link_setup(struct media_entity *entity,
			     const struct media_pad *local,
			     const struct media_pad *remote, u32 flags)
{
	if ((local->flags & MEDIA_PAD_FL_SOURCE) &&
	    (flags & MEDIA_LNK_FL_ENABLED)) {
		struct v4l2_subdev *sd;
		struct csiphy_device *csiphy;
		struct csid_device *csid;

		if (media_entity_remote_pad(local))
			return -EBUSY;

		sd = media_entity_to_v4l2_subdev(entity);
		csiphy = v4l2_get_subdevdata(sd);

		sd = media_entity_to_v4l2_subdev(remote->entity);
		csid = v4l2_get_subdevdata(sd);

		csiphy->cfg.csid_id = csid->id;
	}

	return 0;
}
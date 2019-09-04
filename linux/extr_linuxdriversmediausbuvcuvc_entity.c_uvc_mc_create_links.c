#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int u32 ;
struct uvc_video_chain {int /*<<< orphan*/  dev; } ;
struct media_entity {int dummy; } ;
struct TYPE_6__ {struct media_entity entity; } ;
struct uvc_entity {unsigned int num_pads; TYPE_3__ subdev; TYPE_2__* vdev; int /*<<< orphan*/ * baSourceID; TYPE_1__* pads; } ;
struct TYPE_5__ {struct media_entity entity; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 int MEDIA_PAD_FL_SINK ; 
 scalar_t__ UVC_ENTITY_TYPE (struct uvc_entity*) ; 
 scalar_t__ UVC_TT_STREAMING ; 
 int media_create_pad_link (struct media_entity*,unsigned int,struct media_entity*,unsigned int,int const) ; 
 struct uvc_entity* uvc_entity_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_mc_create_links(struct uvc_video_chain *chain,
				    struct uvc_entity *entity)
{
	const u32 flags = MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE;
	struct media_entity *sink;
	unsigned int i;
	int ret;

	sink = (UVC_ENTITY_TYPE(entity) == UVC_TT_STREAMING)
	     ? (entity->vdev ? &entity->vdev->entity : NULL)
	     : &entity->subdev.entity;
	if (sink == NULL)
		return 0;

	for (i = 0; i < entity->num_pads; ++i) {
		struct media_entity *source;
		struct uvc_entity *remote;
		u8 remote_pad;

		if (!(entity->pads[i].flags & MEDIA_PAD_FL_SINK))
			continue;

		remote = uvc_entity_by_id(chain->dev, entity->baSourceID[i]);
		if (remote == NULL)
			return -EINVAL;

		source = (UVC_ENTITY_TYPE(remote) == UVC_TT_STREAMING)
		       ? (remote->vdev ? &remote->vdev->entity : NULL)
		       : &remote->subdev.entity;
		if (source == NULL)
			continue;

		remote_pad = remote->num_pads - 1;
		ret = media_create_pad_link(source, remote_pad,
					       sink, i, flags);
		if (ret < 0)
			return ret;
	}

	return 0;
}
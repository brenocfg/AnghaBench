#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int const u32 ;
struct media_link {int const flags; TYPE_2__* sink; TYPE_1__* source; } ;
struct TYPE_7__ {struct media_device* mdev; } ;
struct media_entity {TYPE_3__ graph_obj; scalar_t__ stream_count; } ;
struct media_device {TYPE_4__* ops; } ;
struct TYPE_8__ {int (* link_notify ) (struct media_link*,int const,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct media_entity* entity; } ;
struct TYPE_5__ {struct media_entity* entity; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_DEV_NOTIFY_POST_LINK_CH ; 
 int /*<<< orphan*/  MEDIA_DEV_NOTIFY_PRE_LINK_CH ; 
 int MEDIA_LNK_FL_DYNAMIC ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 int __media_entity_setup_link_notify (struct media_link*,int const) ; 
 int stub1 (struct media_link*,int const,int /*<<< orphan*/ ) ; 
 int stub2 (struct media_link*,int const,int /*<<< orphan*/ ) ; 

int __media_entity_setup_link(struct media_link *link, u32 flags)
{
	const u32 mask = MEDIA_LNK_FL_ENABLED;
	struct media_device *mdev;
	struct media_entity *source, *sink;
	int ret = -EBUSY;

	if (link == NULL)
		return -EINVAL;

	/* The non-modifiable link flags must not be modified. */
	if ((link->flags & ~mask) != (flags & ~mask))
		return -EINVAL;

	if (link->flags & MEDIA_LNK_FL_IMMUTABLE)
		return link->flags == flags ? 0 : -EINVAL;

	if (link->flags == flags)
		return 0;

	source = link->source->entity;
	sink = link->sink->entity;

	if (!(link->flags & MEDIA_LNK_FL_DYNAMIC) &&
	    (source->stream_count || sink->stream_count))
		return -EBUSY;

	mdev = source->graph_obj.mdev;

	if (mdev->ops && mdev->ops->link_notify) {
		ret = mdev->ops->link_notify(link, flags,
					     MEDIA_DEV_NOTIFY_PRE_LINK_CH);
		if (ret < 0)
			return ret;
	}

	ret = __media_entity_setup_link_notify(link, flags);

	if (mdev->ops && mdev->ops->link_notify)
		mdev->ops->link_notify(link, flags,
				       MEDIA_DEV_NOTIFY_POST_LINK_CH);

	return ret;
}
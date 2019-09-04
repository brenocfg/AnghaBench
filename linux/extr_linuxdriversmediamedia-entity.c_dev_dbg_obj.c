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
struct media_gobj {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dev_dbg_obj(const char *event_name,  struct media_gobj *gobj)
{
#if defined(DEBUG) || defined (CONFIG_DYNAMIC_DEBUG)
	switch (media_type(gobj)) {
	case MEDIA_GRAPH_ENTITY:
		dev_dbg(gobj->mdev->dev,
			"%s id %u: entity '%s'\n",
			event_name, media_id(gobj),
			gobj_to_entity(gobj)->name);
		break;
	case MEDIA_GRAPH_LINK:
	{
		struct media_link *link = gobj_to_link(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s link id %u ==> id %u\n",
			event_name, media_id(gobj),
			media_type(link->gobj0) == MEDIA_GRAPH_PAD ?
				"data" : "interface",
			media_id(link->gobj0),
			media_id(link->gobj1));
		break;
	}
	case MEDIA_GRAPH_PAD:
	{
		struct media_pad *pad = gobj_to_pad(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s%spad '%s':%d\n",
			event_name, media_id(gobj),
			pad->flags & MEDIA_PAD_FL_SINK   ? "sink " : "",
			pad->flags & MEDIA_PAD_FL_SOURCE ? "source " : "",
			pad->entity->name, pad->index);
		break;
	}
	case MEDIA_GRAPH_INTF_DEVNODE:
	{
		struct media_interface *intf = gobj_to_intf(gobj);
		struct media_intf_devnode *devnode = intf_to_devnode(intf);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: intf_devnode %s - major: %d, minor: %d\n",
			event_name, media_id(gobj),
			intf_type(intf),
			devnode->major, devnode->minor);
		break;
	}
	}
#endif
}
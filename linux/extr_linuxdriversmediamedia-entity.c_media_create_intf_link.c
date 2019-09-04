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
struct media_link {int flags; int /*<<< orphan*/  graph_obj; struct media_entity* entity; struct media_interface* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;
struct media_interface {TYPE_1__ graph_obj; int /*<<< orphan*/  links; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_GRAPH_LINK ; 
 int MEDIA_LNK_FL_INTERFACE_LINK ; 
 struct media_link* media_add_link (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_gobj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct media_link *media_create_intf_link(struct media_entity *entity,
					    struct media_interface *intf,
					    u32 flags)
{
	struct media_link *link;

	link = media_add_link(&intf->links);
	if (link == NULL)
		return NULL;

	link->intf = intf;
	link->entity = entity;
	link->flags = flags | MEDIA_LNK_FL_INTERFACE_LINK;

	/* Initialize graph object embedded at the new link */
	media_gobj_create(intf->graph_obj.mdev, MEDIA_GRAPH_LINK,
			&link->graph_obj);

	return link;
}
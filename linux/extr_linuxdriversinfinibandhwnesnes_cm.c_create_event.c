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
struct nes_cm_node {scalar_t__ cm_id; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rem_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rem_port; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  loc_addr; scalar_t__ cm_id; } ;
struct nes_cm_event {int type; TYPE_1__ cm_info; struct nes_cm_node* cm_node; } ;
typedef  enum nes_cm_event_type { ____Placeholder_nes_cm_event_type } nes_cm_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 struct nes_cm_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_cm_post_event (struct nes_cm_event*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cm_node*,struct nes_cm_event*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nes_cm_event *create_event(struct nes_cm_node *	cm_node,
					 enum nes_cm_event_type type)
{
	struct nes_cm_event *event;

	if (!cm_node->cm_id)
		return NULL;

	/* allocate an empty event */
	event = kzalloc(sizeof(*event), GFP_ATOMIC);

	if (!event)
		return NULL;

	event->type = type;
	event->cm_node = cm_node;
	event->cm_info.rem_addr = cm_node->rem_addr;
	event->cm_info.loc_addr = cm_node->loc_addr;
	event->cm_info.rem_port = cm_node->rem_port;
	event->cm_info.loc_port = cm_node->loc_port;
	event->cm_info.cm_id = cm_node->cm_id;

	nes_debug(NES_DBG_CM, "cm_node=%p Created event=%p, type=%u, "
		  "dst_addr=%08x[%x], src_addr=%08x[%x]\n",
		  cm_node, event, type, event->cm_info.loc_addr,
		  event->cm_info.loc_port, event->cm_info.rem_addr,
		  event->cm_info.rem_port);

	nes_cm_post_event(event);
	return event;
}
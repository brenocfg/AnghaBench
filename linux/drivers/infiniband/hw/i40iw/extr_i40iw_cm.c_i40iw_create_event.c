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
struct i40iw_cm_node {int /*<<< orphan*/  dev; scalar_t__ cm_id; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rem_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; scalar_t__ cm_id; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_port; } ;
struct i40iw_cm_event {int type; TYPE_1__ cm_info; struct i40iw_cm_node* cm_node; } ;
typedef  enum i40iw_cm_event_type { ____Placeholder_i40iw_cm_event_type } i40iw_cm_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  I40IW_DEBUG_CM ; 
 int /*<<< orphan*/  i40iw_cm_post_event (struct i40iw_cm_event*) ; 
 int /*<<< orphan*/  i40iw_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i40iw_cm_node*,struct i40iw_cm_event*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40iw_cm_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct i40iw_cm_event *i40iw_create_event(struct i40iw_cm_node *cm_node,
						 enum i40iw_cm_event_type type)
{
	struct i40iw_cm_event *event;

	if (!cm_node->cm_id)
		return NULL;

	event = kzalloc(sizeof(*event), GFP_ATOMIC);

	if (!event)
		return NULL;

	event->type = type;
	event->cm_node = cm_node;
	memcpy(event->cm_info.rem_addr, cm_node->rem_addr, sizeof(event->cm_info.rem_addr));
	memcpy(event->cm_info.loc_addr, cm_node->loc_addr, sizeof(event->cm_info.loc_addr));
	event->cm_info.rem_port = cm_node->rem_port;
	event->cm_info.loc_port = cm_node->loc_port;
	event->cm_info.cm_id = cm_node->cm_id;

	i40iw_debug(cm_node->dev,
		    I40IW_DEBUG_CM,
		    "node=%p event=%p type=%u dst=%pI4 src=%pI4\n",
		    cm_node,
		    event,
		    type,
		    event->cm_info.loc_addr,
		    event->cm_info.rem_addr);

	i40iw_cm_post_event(event);
	return event;
}
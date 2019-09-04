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
typedef  int /*<<< orphan*/  u32 ;
struct fw_node {int color; int node_id; int port_count; int /*<<< orphan*/  link; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  initiated_reset; int /*<<< orphan*/  phy_speed; int /*<<< orphan*/  link_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int LOCAL_BUS ; 
 int /*<<< orphan*/  SELF_ID_LINK_ON (int /*<<< orphan*/ ) ; 
 int SELF_ID_PHY_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELF_ID_PHY_INITIATOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELF_ID_PHY_SPEED (int /*<<< orphan*/ ) ; 
 struct fw_node* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  struct_size (struct fw_node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct fw_node *fw_node_create(u32 sid, int port_count, int color)
{
	struct fw_node *node;

	node = kzalloc(struct_size(node, ports, port_count), GFP_ATOMIC);
	if (node == NULL)
		return NULL;

	node->color = color;
	node->node_id = LOCAL_BUS | SELF_ID_PHY_ID(sid);
	node->link_on = SELF_ID_LINK_ON(sid);
	node->phy_speed = SELF_ID_PHY_SPEED(sid);
	node->initiated_reset = SELF_ID_PHY_INITIATOR(sid);
	node->port_count = port_count;

	refcount_set(&node->ref_count, 1);
	INIT_LIST_HEAD(&node->link);

	return node;
}
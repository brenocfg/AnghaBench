#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int /*<<< orphan*/  next; } ;
struct fw_node {scalar_t__ port_count; scalar_t__ color; struct list_head link; TYPE_2__** ports; int /*<<< orphan*/  max_hops; scalar_t__ initiated_reset; scalar_t__ link_on; int /*<<< orphan*/  node_id; } ;
struct fw_card {scalar_t__ color; struct fw_node* irm_node; struct fw_node* root_node; TYPE_1__* local_node; } ;
struct TYPE_4__ {scalar_t__ color; struct list_head link; } ;
struct TYPE_3__ {struct list_head link; } ;

/* Variables and functions */
 int FW_NODE_INITIATED_RESET ; 
 int FW_NODE_LINK_OFF ; 
 int FW_NODE_LINK_ON ; 
 int FW_NODE_UPDATED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  for_each_fw_node (struct fw_card*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct fw_node* fw_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_node_event (struct fw_card*,struct fw_node*,int) ; 
 int /*<<< orphan*/  fw_node_put (struct fw_node*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  move_tree (struct fw_node*,struct fw_node*,int) ; 
 int /*<<< orphan*/  report_found_node ; 
 int /*<<< orphan*/  report_lost_node ; 

__attribute__((used)) static void update_tree(struct fw_card *card, struct fw_node *root)
{
	struct list_head list0, list1;
	struct fw_node *node0, *node1, *next1;
	int i, event;

	INIT_LIST_HEAD(&list0);
	list_add_tail(&card->local_node->link, &list0);
	INIT_LIST_HEAD(&list1);
	list_add_tail(&root->link, &list1);

	node0 = fw_node(list0.next);
	node1 = fw_node(list1.next);

	while (&node0->link != &list0) {
		WARN_ON(node0->port_count != node1->port_count);

		if (node0->link_on && !node1->link_on)
			event = FW_NODE_LINK_OFF;
		else if (!node0->link_on && node1->link_on)
			event = FW_NODE_LINK_ON;
		else if (node1->initiated_reset && node1->link_on)
			event = FW_NODE_INITIATED_RESET;
		else
			event = FW_NODE_UPDATED;

		node0->node_id = node1->node_id;
		node0->color = card->color;
		node0->link_on = node1->link_on;
		node0->initiated_reset = node1->initiated_reset;
		node0->max_hops = node1->max_hops;
		node1->color = card->color;
		fw_node_event(card, node0, event);

		if (card->root_node == node1)
			card->root_node = node0;
		if (card->irm_node == node1)
			card->irm_node = node0;

		for (i = 0; i < node0->port_count; i++) {
			if (node0->ports[i] && node1->ports[i]) {
				/*
				 * This port didn't change, queue the
				 * connected node for further
				 * investigation.
				 */
				if (node0->ports[i]->color == card->color)
					continue;
				list_add_tail(&node0->ports[i]->link, &list0);
				list_add_tail(&node1->ports[i]->link, &list1);
			} else if (node0->ports[i]) {
				/*
				 * The nodes connected here were
				 * unplugged; unref the lost nodes and
				 * queue FW_NODE_LOST callbacks for
				 * them.
				 */

				for_each_fw_node(card, node0->ports[i],
						 report_lost_node);
				node0->ports[i] = NULL;
			} else if (node1->ports[i]) {
				/*
				 * One or more node were connected to
				 * this port. Move the new nodes into
				 * the tree and queue FW_NODE_CREATED
				 * callbacks for them.
				 */
				move_tree(node0, node1, i);
				for_each_fw_node(card, node0->ports[i],
						 report_found_node);
			}
		}

		node0 = fw_node(node0->link.next);
		next1 = fw_node(node1->link.next);
		fw_node_put(node1);
		node1 = next1;
	}
}
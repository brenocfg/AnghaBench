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
typedef  int /*<<< orphan*/  u32 ;
struct list_head {struct list_head* prev; } ;
struct TYPE_2__ {struct list_head* next; } ;
struct fw_node {int color; scalar_t__ phy_speed; TYPE_1__ link; struct fw_node** ports; } ;
struct fw_card {size_t color; int node_id; int gap_count; int beta_repeaters_present; struct fw_node* irm_node; struct fw_node* root_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ SCODE_BETA ; 
#define  SELFID_PORT_CHILD 129 
#define  SELFID_PORT_PARENT 128 
 scalar_t__ SELF_ID_CONTENDER (int /*<<< orphan*/ ) ; 
 int SELF_ID_GAP_COUNT (int /*<<< orphan*/ ) ; 
 int SELF_ID_PHY_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __list_del (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/ * count_ports (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  fw_err (struct fw_card*,char*,...) ; 
 struct fw_node* fw_node (struct list_head*) ; 
 struct fw_node* fw_node_create (int /*<<< orphan*/ ,int,size_t) ; 
 int get_port_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  update_hop_count (struct fw_node*) ; 

__attribute__((used)) static struct fw_node *build_tree(struct fw_card *card,
				  u32 *sid, int self_id_count)
{
	struct fw_node *node, *child, *local_node, *irm_node;
	struct list_head stack, *h;
	u32 *next_sid, *end, q;
	int i, port_count, child_port_count, phy_id, parent_count, stack_depth;
	int gap_count;
	bool beta_repeaters_present;

	local_node = NULL;
	node = NULL;
	INIT_LIST_HEAD(&stack);
	stack_depth = 0;
	end = sid + self_id_count;
	phy_id = 0;
	irm_node = NULL;
	gap_count = SELF_ID_GAP_COUNT(*sid);
	beta_repeaters_present = false;

	while (sid < end) {
		next_sid = count_ports(sid, &port_count, &child_port_count);

		if (next_sid == NULL) {
			fw_err(card, "inconsistent extended self IDs\n");
			return NULL;
		}

		q = *sid;
		if (phy_id != SELF_ID_PHY_ID(q)) {
			fw_err(card, "PHY ID mismatch in self ID: %d != %d\n",
			       phy_id, SELF_ID_PHY_ID(q));
			return NULL;
		}

		if (child_port_count > stack_depth) {
			fw_err(card, "topology stack underflow\n");
			return NULL;
		}

		/*
		 * Seek back from the top of our stack to find the
		 * start of the child nodes for this node.
		 */
		for (i = 0, h = &stack; i < child_port_count; i++)
			h = h->prev;
		/*
		 * When the stack is empty, this yields an invalid value,
		 * but that pointer will never be dereferenced.
		 */
		child = fw_node(h);

		node = fw_node_create(q, port_count, card->color);
		if (node == NULL) {
			fw_err(card, "out of memory while building topology\n");
			return NULL;
		}

		if (phy_id == (card->node_id & 0x3f))
			local_node = node;

		if (SELF_ID_CONTENDER(q))
			irm_node = node;

		parent_count = 0;

		for (i = 0; i < port_count; i++) {
			switch (get_port_type(sid, i)) {
			case SELFID_PORT_PARENT:
				/*
				 * Who's your daddy?  We dont know the
				 * parent node at this time, so we
				 * temporarily abuse node->color for
				 * remembering the entry in the
				 * node->ports array where the parent
				 * node should be.  Later, when we
				 * handle the parent node, we fix up
				 * the reference.
				 */
				parent_count++;
				node->color = i;
				break;

			case SELFID_PORT_CHILD:
				node->ports[i] = child;
				/*
				 * Fix up parent reference for this
				 * child node.
				 */
				child->ports[child->color] = node;
				child->color = card->color;
				child = fw_node(child->link.next);
				break;
			}
		}

		/*
		 * Check that the node reports exactly one parent
		 * port, except for the root, which of course should
		 * have no parents.
		 */
		if ((next_sid == end && parent_count != 0) ||
		    (next_sid < end && parent_count != 1)) {
			fw_err(card, "parent port inconsistency for node %d: "
			       "parent_count=%d\n", phy_id, parent_count);
			return NULL;
		}

		/* Pop the child nodes off the stack and push the new node. */
		__list_del(h->prev, &stack);
		list_add_tail(&node->link, &stack);
		stack_depth += 1 - child_port_count;

		if (node->phy_speed == SCODE_BETA &&
		    parent_count + child_port_count > 1)
			beta_repeaters_present = true;

		/*
		 * If PHYs report different gap counts, set an invalid count
		 * which will force a gap count reconfiguration and a reset.
		 */
		if (SELF_ID_GAP_COUNT(q) != gap_count)
			gap_count = 0;

		update_hop_count(node);

		sid = next_sid;
		phy_id++;
	}

	card->root_node = node;
	card->irm_node = irm_node;
	card->gap_count = gap_count;
	card->beta_repeaters_present = beta_repeaters_present;

	return local_node;
}
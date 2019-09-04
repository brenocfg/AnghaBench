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
struct fw_node {int port_count; struct fw_node** ports; } ;

/* Variables and functions */

__attribute__((used)) static void move_tree(struct fw_node *node0, struct fw_node *node1, int port)
{
	struct fw_node *tree;
	int i;

	tree = node1->ports[port];
	node0->ports[port] = tree;
	for (i = 0; i < tree->port_count; i++) {
		if (tree->ports[i] == node1) {
			tree->ports[i] = node0;
			break;
		}
	}
}
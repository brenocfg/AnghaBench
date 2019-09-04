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
struct fw_node {int dummy; } ;
struct fw_card {scalar_t__ bm_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_NODE_DESTROYED ; 
 int /*<<< orphan*/  fw_node_event (struct fw_card*,struct fw_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_node_put (struct fw_node*) ; 

__attribute__((used)) static void report_lost_node(struct fw_card *card,
			     struct fw_node *node, struct fw_node *parent)
{
	fw_node_event(card, node, FW_NODE_DESTROYED);
	fw_node_put(node);

	/* Topology has changed - reset bus manager retry counter */
	card->bm_retries = 0;
}
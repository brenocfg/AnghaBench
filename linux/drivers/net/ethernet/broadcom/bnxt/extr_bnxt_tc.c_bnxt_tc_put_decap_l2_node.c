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
struct bnxt_tc_l2_node {scalar_t__ refcount; int /*<<< orphan*/  node; } ;
struct bnxt_tc_info {int /*<<< orphan*/  decap_l2_ht_params; int /*<<< orphan*/  decap_l2_table; } ;
struct bnxt_tc_flow_node {int /*<<< orphan*/  decap_l2_list_node; struct bnxt_tc_l2_node* decap_l2_node; } ;
struct bnxt {int /*<<< orphan*/  dev; struct bnxt_tc_info* tc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct bnxt_tc_l2_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rcu ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_tc_put_decap_l2_node(struct bnxt *bp,
				      struct bnxt_tc_flow_node *flow_node)
{
	struct bnxt_tc_l2_node *decap_l2_node = flow_node->decap_l2_node;
	struct bnxt_tc_info *tc_info = bp->tc_info;
	int rc;

	/* remove flow_node from the decap L2 sharing flow list */
	list_del(&flow_node->decap_l2_list_node);
	if (--decap_l2_node->refcount == 0) {
		rc =  rhashtable_remove_fast(&tc_info->decap_l2_table,
					     &decap_l2_node->node,
					     tc_info->decap_l2_ht_params);
		if (rc)
			netdev_err(bp->dev, "rhashtable_remove_fast rc=%d", rc);
		kfree_rcu(decap_l2_node, rcu);
	}
}
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
typedef  int /*<<< orphan*/  u8 ;
struct qtnf_sta_list {int /*<<< orphan*/  size; } ;
struct qtnf_vif {int /*<<< orphan*/  generation; struct qtnf_sta_list sta_list; } ;
struct qtnf_sta_node {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qtnf_sta_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct qtnf_sta_node* qtnf_sta_list_lookup (struct qtnf_sta_list*,int /*<<< orphan*/  const*) ; 

bool qtnf_sta_list_del(struct qtnf_vif *vif, const u8 *mac)
{
	struct qtnf_sta_list *list = &vif->sta_list;
	struct qtnf_sta_node *node;
	bool ret = false;

	node = qtnf_sta_list_lookup(list, mac);

	if (node) {
		list_del(&node->list);
		atomic_dec(&list->size);
		kfree(node);
		++vif->generation;
		ret = true;
	}

	return ret;
}
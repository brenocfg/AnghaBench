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
struct icc_node {int /*<<< orphan*/  req_list; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icc_idr ; 
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct icc_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct icc_node* node_find (int) ; 

void icc_node_destroy(int id)
{
	struct icc_node *node;

	mutex_lock(&icc_lock);

	node = node_find(id);
	if (node) {
		idr_remove(&icc_idr, node->id);
		WARN_ON(!hlist_empty(&node->req_list));
	}

	mutex_unlock(&icc_lock);

	kfree(node);
}
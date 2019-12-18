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
struct icc_provider {int /*<<< orphan*/  nodes; } ;
struct icc_node {int /*<<< orphan*/  node_list; struct icc_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void icc_node_add(struct icc_node *node, struct icc_provider *provider)
{
	mutex_lock(&icc_lock);

	node->provider = provider;
	list_add_tail(&node->node_list, &provider->nodes);

	mutex_unlock(&icc_lock);
}
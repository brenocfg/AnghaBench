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
struct binder_node {int dummy; } ;

/* Variables and functions */
 int binder_dec_node_nilocked (struct binder_node*,int,int) ; 
 int /*<<< orphan*/  binder_free_node (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_lock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_unlock (struct binder_node*) ; 

__attribute__((used)) static void binder_dec_node(struct binder_node *node, int strong, int internal)
{
	bool free_node;

	binder_node_inner_lock(node);
	free_node = binder_dec_node_nilocked(node, strong, internal);
	binder_node_inner_unlock(node);
	if (free_node)
		binder_free_node(node);
}
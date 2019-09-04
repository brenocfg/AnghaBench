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
struct hfi1_affinity_node {int node; int /*<<< orphan*/  list; int /*<<< orphan*/  comp_vect_affinity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_percpu (int /*<<< orphan*/ ) ; 
 struct hfi1_affinity_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static struct hfi1_affinity_node *node_affinity_allocate(int node)
{
	struct hfi1_affinity_node *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return NULL;
	entry->node = node;
	entry->comp_vect_affinity = alloc_percpu(u16);
	INIT_LIST_HEAD(&entry->list);

	return entry;
}
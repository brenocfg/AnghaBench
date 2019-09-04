#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* cluster_hotplug_mask ; 
 int /*<<< orphan*/  cluster_masks ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int alloc_clustermask(unsigned int cpu, int node)
{
	if (per_cpu(cluster_masks, cpu))
		return 0;
	/*
	 * If a hotplug spare mask exists, check whether it's on the right
	 * node. If not, free it and allocate a new one.
	 */
	if (cluster_hotplug_mask) {
		if (cluster_hotplug_mask->node == node)
			return 0;
		kfree(cluster_hotplug_mask);
	}

	cluster_hotplug_mask = kzalloc_node(sizeof(*cluster_hotplug_mask),
					    GFP_KERNEL, node);
	if (!cluster_hotplug_mask)
		return -ENOMEM;
	cluster_hotplug_mask->node = node;
	return 0;
}
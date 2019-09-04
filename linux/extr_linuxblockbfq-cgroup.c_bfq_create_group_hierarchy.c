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
struct TYPE_2__ {int /*<<< orphan*/ * service_tree; } ;
struct bfq_group {TYPE_1__ sched_data; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 int BFQ_IOPRIO_CLASSES ; 
 int /*<<< orphan*/  BFQ_SERVICE_TREE_INIT ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 struct bfq_group* kmalloc_node (int,int,int) ; 

struct bfq_group *bfq_create_group_hierarchy(struct bfq_data *bfqd, int node)
{
	struct bfq_group *bfqg;
	int i;

	bfqg = kmalloc_node(sizeof(*bfqg), GFP_KERNEL | __GFP_ZERO, node);
	if (!bfqg)
		return NULL;

	for (i = 0; i < BFQ_IOPRIO_CLASSES; i++)
		bfqg->sched_data.service_tree[i] = BFQ_SERVICE_TREE_INIT;

	return bfqg;
}
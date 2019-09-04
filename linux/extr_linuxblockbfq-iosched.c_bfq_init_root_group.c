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
struct TYPE_2__ {int /*<<< orphan*/  bfq_class_idle_last_service; int /*<<< orphan*/ * service_tree; } ;
struct bfq_group {TYPE_1__ sched_data; int /*<<< orphan*/  rq_pos_tree; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 int BFQ_IOPRIO_CLASSES ; 
 int /*<<< orphan*/  BFQ_SERVICE_TREE_INIT ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void bfq_init_root_group(struct bfq_group *root_group,
				struct bfq_data *bfqd)
{
	int i;

#ifdef CONFIG_BFQ_GROUP_IOSCHED
	root_group->entity.parent = NULL;
	root_group->my_entity = NULL;
	root_group->bfqd = bfqd;
#endif
	root_group->rq_pos_tree = RB_ROOT;
	for (i = 0; i < BFQ_IOPRIO_CLASSES; i++)
		root_group->sched_data.service_tree[i] = BFQ_SERVICE_TREE_INIT;
	root_group->sched_data.bfq_class_idle_last_service = jiffies;
}
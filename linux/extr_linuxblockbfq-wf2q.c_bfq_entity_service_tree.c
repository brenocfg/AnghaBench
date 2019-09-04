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
struct bfq_service_tree {int dummy; } ;
struct bfq_sched_data {struct bfq_service_tree* service_tree; } ;
struct bfq_entity {struct bfq_sched_data* sched_data; } ;

/* Variables and functions */
 unsigned int bfq_class_idx (struct bfq_entity*) ; 

struct bfq_service_tree *bfq_entity_service_tree(struct bfq_entity *entity)
{
	struct bfq_sched_data *sched_data = entity->sched_data;
	unsigned int idx = bfq_class_idx(entity);

	return sched_data->service_tree + idx;
}
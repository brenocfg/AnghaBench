#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; } ;
struct cfq_group {TYPE_2__** service_trees; TYPE_1__ service_tree_idle; } ;
struct cfq_data {int dummy; } ;
typedef  enum wl_class_t { ____Placeholder_wl_class_t } wl_class_t ;
struct TYPE_4__ {int count; } ;

/* Variables and functions */
 size_t ASYNC_WORKLOAD ; 
 int IDLE_WORKLOAD ; 
 size_t SYNC_NOIDLE_WORKLOAD ; 
 size_t SYNC_WORKLOAD ; 

__attribute__((used)) static inline int cfq_group_busy_queues_wl(enum wl_class_t wl_class,
					struct cfq_data *cfqd,
					struct cfq_group *cfqg)
{
	if (wl_class == IDLE_WORKLOAD)
		return cfqg->service_tree_idle.count;

	return cfqg->service_trees[wl_class][ASYNC_WORKLOAD].count +
		cfqg->service_trees[wl_class][SYNC_NOIDLE_WORKLOAD].count +
		cfqg->service_trees[wl_class][SYNC_WORKLOAD].count;
}
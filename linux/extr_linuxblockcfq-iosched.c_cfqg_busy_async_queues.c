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
struct cfq_group {TYPE_1__** service_trees; } ;
struct cfq_data {int dummy; } ;
struct TYPE_2__ {int count; } ;

/* Variables and functions */
 size_t ASYNC_WORKLOAD ; 
 size_t BE_WORKLOAD ; 
 size_t RT_WORKLOAD ; 

__attribute__((used)) static inline int cfqg_busy_async_queues(struct cfq_data *cfqd,
					struct cfq_group *cfqg)
{
	return cfqg->service_trees[RT_WORKLOAD][ASYNC_WORKLOAD].count +
		cfqg->service_trees[BE_WORKLOAD][ASYNC_WORKLOAD].count;
}
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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct sdma_rht_node {struct sdma_rht_map_elem** map; } ;
struct sdma_rht_map_elem {size_t mask; struct sdma_engine** sde; } ;
struct sdma_engine {int dummy; } ;
struct hfi1_devdata {int /*<<< orphan*/  sdma_rht; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {struct cpumask cpus_allowed; } ;

/* Variables and functions */
 int cpumask_weight (struct cpumask const*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sdma_rht_node* rhashtable_lookup_fast (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_rht_params ; 
 struct sdma_engine* sdma_select_engine_vl (struct hfi1_devdata*,size_t,size_t) ; 
 unsigned long smp_processor_id () ; 

struct sdma_engine *sdma_select_user_engine(struct hfi1_devdata *dd,
					    u32 selector, u8 vl)
{
	struct sdma_rht_node *rht_node;
	struct sdma_engine *sde = NULL;
	const struct cpumask *current_mask = &current->cpus_allowed;
	unsigned long cpu_id;

	/*
	 * To ensure that always the same sdma engine(s) will be
	 * selected make sure the process is pinned to this CPU only.
	 */
	if (cpumask_weight(current_mask) != 1)
		goto out;

	cpu_id = smp_processor_id();
	rcu_read_lock();
	rht_node = rhashtable_lookup_fast(dd->sdma_rht, &cpu_id,
					  sdma_rht_params);

	if (rht_node && rht_node->map[vl]) {
		struct sdma_rht_map_elem *map = rht_node->map[vl];

		sde = map->sde[selector & map->mask];
	}
	rcu_read_unlock();

	if (sde)
		return sde;

out:
	return sdma_select_engine_vl(dd, selector, vl);
}
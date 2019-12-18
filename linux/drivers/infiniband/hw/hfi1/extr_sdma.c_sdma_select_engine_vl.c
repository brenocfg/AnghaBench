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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct sdma_vl_map {size_t mask; struct sdma_map_elem** map; } ;
struct sdma_map_elem {size_t mask; struct sdma_engine** sde; } ;
struct sdma_engine {int /*<<< orphan*/  this_idx; } ;
struct hfi1_devdata {struct sdma_engine* per_sdma; int /*<<< orphan*/  sdma_map; } ;

/* Variables and functions */
 size_t num_vls ; 
 struct sdma_vl_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_hfi1_sdma_engine_select (struct hfi1_devdata*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sdma_engine *sdma_select_engine_vl(
	struct hfi1_devdata *dd,
	u32 selector,
	u8 vl)
{
	struct sdma_vl_map *m;
	struct sdma_map_elem *e;
	struct sdma_engine *rval;

	/* NOTE This should only happen if SC->VL changed after the initial
	 *      checks on the QP/AH
	 *      Default will return engine 0 below
	 */
	if (vl >= num_vls) {
		rval = NULL;
		goto done;
	}

	rcu_read_lock();
	m = rcu_dereference(dd->sdma_map);
	if (unlikely(!m)) {
		rcu_read_unlock();
		return &dd->per_sdma[0];
	}
	e = m->map[vl & m->mask];
	rval = e->sde[selector & e->mask];
	rcu_read_unlock();

done:
	rval =  !rval ? &dd->per_sdma[0] : rval;
	trace_hfi1_sdma_engine_select(dd, selector, vl, rval->this_idx);
	return rval;
}
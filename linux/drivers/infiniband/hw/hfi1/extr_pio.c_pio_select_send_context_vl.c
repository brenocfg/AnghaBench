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
struct send_context {int dummy; } ;
struct pio_vl_map {size_t mask; struct pio_map_elem** map; } ;
struct pio_map_elem {size_t mask; struct send_context** ksc; } ;
struct hfi1_devdata {TYPE_1__* vld; int /*<<< orphan*/  pio_map; } ;
struct TYPE_2__ {struct send_context* sc; } ;

/* Variables and functions */
 size_t num_vls ; 
 struct pio_vl_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct send_context *pio_select_send_context_vl(struct hfi1_devdata *dd,
						u32 selector, u8 vl)
{
	struct pio_vl_map *m;
	struct pio_map_elem *e;
	struct send_context *rval;

	/*
	 * NOTE This should only happen if SC->VL changed after the initial
	 * checks on the QP/AH
	 * Default will return VL0's send context below
	 */
	if (unlikely(vl >= num_vls)) {
		rval = NULL;
		goto done;
	}

	rcu_read_lock();
	m = rcu_dereference(dd->pio_map);
	if (unlikely(!m)) {
		rcu_read_unlock();
		return dd->vld[0].sc;
	}
	e = m->map[vl & m->mask];
	rval = e->ksc[selector & e->mask];
	rcu_read_unlock();

done:
	rval = !rval ? dd->vld[0].sc : rval;
	return rval;
}
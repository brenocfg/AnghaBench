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
struct sdma_vl_map {int* engine_to_vl; } ;
struct hfi1_devdata {int /*<<< orphan*/  sdma_map; } ;

/* Variables and functions */
 int TXE_NUM_SDMA_ENGINES ; 
 struct sdma_vl_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int engine_to_vl(struct hfi1_devdata *dd, int engine)
{
	struct sdma_vl_map *m;
	int vl;

	/* range check */
	if (engine < 0 || engine >= TXE_NUM_SDMA_ENGINES)
		return -1;

	rcu_read_lock();
	m = rcu_dereference(dd->sdma_map);
	vl = m->engine_to_vl[engine];
	rcu_read_unlock();

	return vl;
}
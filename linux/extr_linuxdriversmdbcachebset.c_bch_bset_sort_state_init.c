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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bset_sort_state {unsigned int page_order; int /*<<< orphan*/  pool; int /*<<< orphan*/  crit_factor; TYPE_1__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  int_sqrt (int) ; 
 int mempool_init_page_pool (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int bch_bset_sort_state_init(struct bset_sort_state *state,
			     unsigned int page_order)
{
	spin_lock_init(&state->time.lock);

	state->page_order = page_order;
	state->crit_factor = int_sqrt(1 << page_order);

	return mempool_init_page_pool(&state->pool, 1, page_order);
}
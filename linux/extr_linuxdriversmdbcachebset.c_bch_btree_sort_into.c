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
typedef  int /*<<< orphan*/  uint64_t ;
struct btree_keys {TYPE_1__* set; } ;
struct btree_iter {int dummy; } ;
struct bset_sort_state {int /*<<< orphan*/  time; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_btree_iter_init (struct btree_keys*,struct btree_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_time_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btree_mergesort (struct btree_keys*,int /*<<< orphan*/ ,struct btree_iter*,int,int) ; 
 int /*<<< orphan*/  local_clock () ; 

void bch_btree_sort_into(struct btree_keys *b, struct btree_keys *new,
			 struct bset_sort_state *state)
{
	uint64_t start_time = local_clock();
	struct btree_iter iter;

	bch_btree_iter_init(b, &iter, NULL);

	btree_mergesort(b, new->set->data, &iter, false, true);

	bch_time_stats_update(&state->time, start_time);

	new->set->size = 0; // XXX: why?
}
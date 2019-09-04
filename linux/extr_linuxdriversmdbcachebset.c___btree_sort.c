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
typedef  int /*<<< orphan*/  uint64_t ;
struct page {int dummy; } ;
struct btree_keys {unsigned int nsets; unsigned int page_order; TYPE_1__* set; } ;
struct btree_iter {int dummy; } ;
struct bset_sort_state {unsigned int page_order; int /*<<< orphan*/  time; int /*<<< orphan*/  pool; } ;
struct bset {scalar_t__ start; int /*<<< orphan*/  keys; int /*<<< orphan*/  version; int /*<<< orphan*/  seq; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; int /*<<< orphan*/  keys; int /*<<< orphan*/  version; int /*<<< orphan*/  seq; int /*<<< orphan*/  magic; } ;
struct TYPE_3__ {TYPE_2__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int GFP_NOWAIT ; 
 int __GFP_NOWARN ; 
 scalar_t__ __get_free_pages (int,unsigned int) ; 
 int /*<<< orphan*/  bch_bset_build_written_tree (struct btree_keys*) ; 
 int /*<<< orphan*/  bch_time_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bset_bkey_last (struct bset*) ; 
 int /*<<< orphan*/  btree_mergesort (struct btree_keys*,struct bset*,struct btree_iter*,int,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct page* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bset* page_address (struct page*) ; 
 int /*<<< orphan*/  swap (struct bset*,TYPE_2__*) ; 
 int /*<<< orphan*/  virt_to_page (struct bset*) ; 

__attribute__((used)) static void __btree_sort(struct btree_keys *b, struct btree_iter *iter,
			 unsigned int start, unsigned int order, bool fixup,
			 struct bset_sort_state *state)
{
	uint64_t start_time;
	bool used_mempool = false;
	struct bset *out = (void *) __get_free_pages(__GFP_NOWARN|GFP_NOWAIT,
						     order);
	if (!out) {
		struct page *outp;

		BUG_ON(order > state->page_order);

		outp = mempool_alloc(&state->pool, GFP_NOIO);
		out = page_address(outp);
		used_mempool = true;
		order = state->page_order;
	}

	start_time = local_clock();

	btree_mergesort(b, out, iter, fixup, false);
	b->nsets = start;

	if (!start && order == b->page_order) {
		/*
		 * Our temporary buffer is the same size as the btree node's
		 * buffer, we can just swap buffers instead of doing a big
		 * memcpy()
		 */

		out->magic	= b->set->data->magic;
		out->seq	= b->set->data->seq;
		out->version	= b->set->data->version;
		swap(out, b->set->data);
	} else {
		b->set[start].data->keys = out->keys;
		memcpy(b->set[start].data->start, out->start,
		       (void *) bset_bkey_last(out) - (void *) out->start);
	}

	if (used_mempool)
		mempool_free(virt_to_page(out), &state->pool);
	else
		free_pages((unsigned long) out, order);

	bch_bset_build_written_tree(b);

	if (!start)
		bch_time_stats_update(&state->time, start_time);
}
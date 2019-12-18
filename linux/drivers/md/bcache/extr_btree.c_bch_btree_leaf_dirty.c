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
struct btree_write {int /*<<< orphan*/ * journal; } ;
struct btree {int /*<<< orphan*/  c; int /*<<< orphan*/  work; int /*<<< orphan*/  written; int /*<<< orphan*/  write_lock; } ;
struct bset {int /*<<< orphan*/  keys; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/  bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HZ ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_dec_bug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_btree_node_write (struct btree*,int /*<<< orphan*/ *) ; 
 struct bset* btree_bset_last (struct btree*) ; 
 struct btree_write* btree_current_write (struct btree*) ; 
 int /*<<< orphan*/  btree_node_dirty (struct btree*) ; 
 TYPE_1__* current ; 
 scalar_t__ journal_pin_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_btree_node_dirty (struct btree*) ; 
 int set_bytes (struct bset*) ; 

__attribute__((used)) static void bch_btree_leaf_dirty(struct btree *b, atomic_t *journal_ref)
{
	struct bset *i = btree_bset_last(b);
	struct btree_write *w = btree_current_write(b);

	lockdep_assert_held(&b->write_lock);

	BUG_ON(!b->written);
	BUG_ON(!i->keys);

	if (!btree_node_dirty(b))
		schedule_delayed_work(&b->work, 30 * HZ);

	set_btree_node_dirty(b);

	if (journal_ref) {
		if (w->journal &&
		    journal_pin_cmp(b->c, w->journal, journal_ref)) {
			atomic_dec_bug(w->journal);
			w->journal = NULL;
		}

		if (!w->journal) {
			w->journal = journal_ref;
			atomic_inc(w->journal);
		}
	}

	/* Force write if set is too big */
	if (set_bytes(i) > PAGE_SIZE - 48 &&
	    !current->bio_list)
		bch_btree_node_write(b, NULL);
}
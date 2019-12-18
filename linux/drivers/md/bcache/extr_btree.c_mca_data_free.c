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
struct btree {TYPE_2__* c; int /*<<< orphan*/  list; int /*<<< orphan*/  keys; TYPE_1__ io_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  btree_cache_freed; int /*<<< orphan*/  btree_cache_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bch_btree_keys_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mca_data_free(struct btree *b)
{
	BUG_ON(b->io_mutex.count != 1);

	bch_btree_keys_free(&b->keys);

	b->c->btree_cache_used--;
	list_move(&b->list, &b->c->btree_cache_freed);
}
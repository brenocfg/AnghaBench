#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bucket {scalar_t__ prio; int /*<<< orphan*/  last_gc; int /*<<< orphan*/  gen; int /*<<< orphan*/  pin; } ;
struct btree {TYPE_1__* c; } ;
struct bkey {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  bucket_lock; scalar_t__ gc_mark_valid; } ;

/* Variables and functions */
 scalar_t__ BTREE_PRIO ; 
 scalar_t__ GC_MARK (struct bucket*) ; 
 scalar_t__ GC_MARK_METADATA ; 
 scalar_t__ KEY_DIRTY (struct bkey const*) ; 
 unsigned int KEY_PTRS (struct bkey const*) ; 
 struct bucket* PTR_BUCKET (TYPE_1__*,struct bkey const*,unsigned int) ; 
 int /*<<< orphan*/  PTR_BUCKET_NR (TYPE_1__*,struct bkey const*,unsigned int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_extent_to_text (char*,int,struct bkey const*) ; 
 int /*<<< orphan*/  btree_bug (struct btree*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ptr_available (TYPE_1__*,struct bkey const*,unsigned int) ; 

__attribute__((used)) static bool btree_ptr_bad_expensive(struct btree *b, const struct bkey *k)
{
	unsigned int i;
	char buf[80];
	struct bucket *g;

	if (mutex_trylock(&b->c->bucket_lock)) {
		for (i = 0; i < KEY_PTRS(k); i++)
			if (ptr_available(b->c, k, i)) {
				g = PTR_BUCKET(b->c, k, i);

				if (KEY_DIRTY(k) ||
				    g->prio != BTREE_PRIO ||
				    (b->c->gc_mark_valid &&
				     GC_MARK(g) != GC_MARK_METADATA))
					goto err;
			}

		mutex_unlock(&b->c->bucket_lock);
	}

	return false;
err:
	mutex_unlock(&b->c->bucket_lock);
	bch_extent_to_text(buf, sizeof(buf), k);
	btree_bug(b,
"inconsistent btree pointer %s: bucket %zi pin %i prio %i gen %i last_gc %i mark %llu",
		  buf, PTR_BUCKET_NR(b->c, k, i), atomic_read(&g->pin),
		  g->prio, g->gen, g->last_gc, GC_MARK(g));
	return true;
}
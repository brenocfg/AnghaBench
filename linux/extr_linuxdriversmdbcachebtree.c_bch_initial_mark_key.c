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
struct cache_set {int dummy; } ;
struct bucket {scalar_t__ prio; int /*<<< orphan*/  gen; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTREE_PRIO ; 
 scalar_t__ INITIAL_PRIO ; 
 unsigned int KEY_PTRS (struct bkey*) ; 
 struct bucket* PTR_BUCKET (struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  PTR_GEN (struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  ZERO_KEY ; 
 int /*<<< orphan*/  __bch_btree_mark_key (struct cache_set*,int,struct bkey*) ; 
 scalar_t__ bkey_cmp (struct bkey*,int /*<<< orphan*/ *) ; 
 scalar_t__ ptr_available (struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  ptr_stale (struct cache_set*,struct bkey*,unsigned int) ; 

void bch_initial_mark_key(struct cache_set *c, int level, struct bkey *k)
{
	unsigned int i;

	for (i = 0; i < KEY_PTRS(k); i++)
		if (ptr_available(c, k, i) &&
		    !ptr_stale(c, k, i)) {
			struct bucket *b = PTR_BUCKET(c, k, i);

			b->gen = PTR_GEN(k, i);

			if (level && bkey_cmp(k, &ZERO_KEY))
				b->prio = BTREE_PRIO;
			else if (!level && b->prio == BTREE_PRIO)
				b->prio = INITIAL_PRIO;
		}

	__bch_btree_mark_key(c, level, k);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btree {TYPE_1__* c; int /*<<< orphan*/  key; } ;
struct bkey {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bucket_lock; int /*<<< orphan*/  prio_blocked; } ;

/* Variables and functions */
 unsigned int KEY_PTRS (struct bkey*) ; 
 int /*<<< orphan*/  PTR_BUCKET (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  PTR_CACHE (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  SET_PTR_GEN (struct bkey*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO_KEY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_inc_gen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bkey_copy (struct bkey*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bkey_copy_key (struct bkey*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void make_btree_freeing_key(struct btree *b, struct bkey *k)
{
	unsigned int i;

	mutex_lock(&b->c->bucket_lock);

	atomic_inc(&b->c->prio_blocked);

	bkey_copy(k, &b->key);
	bkey_copy_key(k, &ZERO_KEY);

	for (i = 0; i < KEY_PTRS(k); i++)
		SET_PTR_GEN(k, i,
			    bch_inc_gen(PTR_CACHE(b->c, &b->key, i),
					PTR_BUCKET(b->c, &b->key, i)));

	mutex_unlock(&b->c->bucket_lock);
}
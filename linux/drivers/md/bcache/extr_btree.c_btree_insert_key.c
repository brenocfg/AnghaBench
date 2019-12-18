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
struct btree {int /*<<< orphan*/  keys; int /*<<< orphan*/  key; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 unsigned int BTREE_INSERT_STATUS_NO_INSERT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int bch_btree_insert_key (int /*<<< orphan*/ *,struct bkey*,struct bkey*) ; 
 int /*<<< orphan*/  bch_check_keys (int /*<<< orphan*/ *,char*,unsigned int,char*) ; 
 scalar_t__ bkey_cmp (struct bkey*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_bcache_btree_insert_key (struct btree*,struct bkey*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool btree_insert_key(struct btree *b, struct bkey *k,
			     struct bkey *replace_key)
{
	unsigned int status;

	BUG_ON(bkey_cmp(k, &b->key) > 0);

	status = bch_btree_insert_key(&b->keys, k, replace_key);
	if (status != BTREE_INSERT_STATUS_NO_INSERT) {
		bch_check_keys(&b->keys, "%u for %s", status,
			       replace_key ? "replace" : "insert");

		trace_bcache_btree_insert_key(b, k, replace_key != NULL,
					      status);
		return true;
	} else
		return false;
}
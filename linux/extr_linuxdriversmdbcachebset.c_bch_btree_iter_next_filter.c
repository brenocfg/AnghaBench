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
struct btree_keys {int dummy; } ;
struct btree_iter {int dummy; } ;
struct bkey {int dummy; } ;
typedef  scalar_t__ (* ptr_filter_fn ) (struct btree_keys*,struct bkey*) ;

/* Variables and functions */
 struct bkey* bch_btree_iter_next (struct btree_iter*) ; 

struct bkey *bch_btree_iter_next_filter(struct btree_iter *iter,
					struct btree_keys *b, ptr_filter_fn fn)
{
	struct bkey *ret;

	do {
		ret = bch_btree_iter_next(iter);
	} while (ret && fn(b, ret));

	return ret;
}
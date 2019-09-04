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
struct btree_iter_set {scalar_t__ k; scalar_t__ end; } ;
struct btree_iter {size_t used; struct btree_iter_set* data; } ;

/* Variables and functions */
 scalar_t__ bkey_next (scalar_t__) ; 

__attribute__((used)) static void sort_key_next(struct btree_iter *iter,
			  struct btree_iter_set *i)
{
	i->k = bkey_next(i->k);

	if (i->k == i->end)
		*i = iter->data[--iter->used];
}
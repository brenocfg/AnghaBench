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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct btree {TYPE_2__ keys; } ;
struct TYPE_3__ {scalar_t__ is_extents; } ;

/* Variables and functions */
 scalar_t__ KEY_MAX_U64S ; 
 long bch_btree_keys_u64s_remaining (TYPE_2__*) ; 
 size_t max (long,long) ; 

__attribute__((used)) static size_t insert_u64s_remaining(struct btree *b)
{
	long ret = bch_btree_keys_u64s_remaining(&b->keys);

	/*
	 * Might land in the middle of an existing extent and have to split it
	 */
	if (b->keys.ops->is_extents)
		ret -= KEY_MAX_U64S;

	return max(ret, 0L);
}
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
struct bkey_float {int dummy; } ;

/* Variables and functions */
 int btree_keys_cachelines (struct btree_keys*) ; 

__attribute__((used)) static inline size_t bset_tree_bytes(struct btree_keys *b)
{
	return btree_keys_cachelines(b) * sizeof(struct bkey_float);
}
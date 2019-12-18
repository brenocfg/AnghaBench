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
struct btree {int /*<<< orphan*/  keys; } ;
struct bset {int dummy; } ;
struct TYPE_2__ {struct bset* data; } ;

/* Variables and functions */
 TYPE_1__* bset_tree_last (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct bset *btree_bset_last(struct btree *b)
{
	return bset_tree_last(&b->keys)->data;
}
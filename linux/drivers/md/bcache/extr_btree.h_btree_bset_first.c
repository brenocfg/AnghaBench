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
struct TYPE_4__ {TYPE_1__* set; } ;
struct btree {TYPE_2__ keys; } ;
struct bset {int dummy; } ;
struct TYPE_3__ {struct bset* data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bset *btree_bset_first(struct btree *b)
{
	return b->keys.set->data;
}
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
typedef  int /*<<< orphan*/  uint64_t ;
struct bset_tree {int* prev; } ;
typedef  void bkey ;

/* Variables and functions */
 scalar_t__ tree_to_bkey (struct bset_tree*,unsigned int) ; 

__attribute__((used)) static struct bkey *tree_to_prev_bkey(struct bset_tree *t, unsigned int j)
{
	return (void *) (((uint64_t *) tree_to_bkey(t, j)) - t->prev[j]);
}
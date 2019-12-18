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
struct bset_sort_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_btree_sort_partial (struct btree_keys*,int /*<<< orphan*/ ,struct bset_sort_state*) ; 

__attribute__((used)) static inline void bch_btree_sort(struct btree_keys *b,
				  struct bset_sort_state *state)
{
	bch_btree_sort_partial(b, 0, state);
}
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
struct shadow_spine {int count; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
struct dm_btree_value_type {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int bn_shadow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_btree_value_type*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_block_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int shadow_step(struct shadow_spine *s, dm_block_t b,
		struct dm_btree_value_type *vt)
{
	int r;

	if (s->count == 2) {
		unlock_block(s->info, s->nodes[0]);
		s->nodes[0] = s->nodes[1];
		s->count--;
	}

	r = bn_shadow(s->info, b, vt, s->nodes + s->count);
	if (!r) {
		if (!s->count)
			s->root = dm_block_location(s->nodes[0]);

		s->count++;
	}

	return r;
}
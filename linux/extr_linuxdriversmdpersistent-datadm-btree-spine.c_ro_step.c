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
struct ro_spine {int count; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int bn_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ro_step(struct ro_spine *s, dm_block_t new_child)
{
	int r;

	if (s->count == 2) {
		unlock_block(s->info, s->nodes[0]);
		s->nodes[0] = s->nodes[1];
		s->count--;
	}

	r = bn_read_lock(s->info, new_child, s->nodes + s->count);
	if (!r)
		s->count++;

	return r;
}
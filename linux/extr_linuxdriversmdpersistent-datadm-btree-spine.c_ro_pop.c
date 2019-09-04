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
struct ro_spine {size_t count; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  unlock_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ro_pop(struct ro_spine *s)
{
	BUG_ON(!s->count);
	--s->count;
	unlock_block(s->info, s->nodes[s->count]);
}
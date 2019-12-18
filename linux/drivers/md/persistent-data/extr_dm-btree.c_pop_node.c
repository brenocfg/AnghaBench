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
struct dm_btree_cursor {size_t depth; TYPE_1__* nodes; int /*<<< orphan*/  info; } ;
struct TYPE_2__ {int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  unlock_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pop_node(struct dm_btree_cursor *c)
{
	c->depth--;
	unlock_block(c->info, c->nodes[c->depth].b);
}
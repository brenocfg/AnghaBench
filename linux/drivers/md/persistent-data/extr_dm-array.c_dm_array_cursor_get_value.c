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
struct dm_array_cursor {int /*<<< orphan*/  index; int /*<<< orphan*/  ab; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 void* element_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dm_array_cursor_get_value(struct dm_array_cursor *c, void **value_le)
{
	*value_le = element_at(c->info, c->ab, c->index);
}
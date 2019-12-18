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
struct rc_map {int /*<<< orphan*/ * scan; int /*<<< orphan*/ * name; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ir_free_table(struct rc_map *rc_map)
{
	rc_map->size = 0;
	kfree(rc_map->name);
	rc_map->name = NULL;
	kfree(rc_map->scan);
	rc_map->scan = NULL;
}
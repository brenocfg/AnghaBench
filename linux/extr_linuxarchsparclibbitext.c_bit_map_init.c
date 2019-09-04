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
struct bit_map {unsigned long* map; int size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int /*<<< orphan*/  memset (struct bit_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void bit_map_init(struct bit_map *t, unsigned long *map, int size)
{
	bitmap_zero(map, size);
	memset(t, 0, sizeof *t);
	spin_lock_init(&t->lock);
	t->map = map;
	t->size = size;
}
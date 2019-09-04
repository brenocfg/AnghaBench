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
struct pio_vl_map {int actual_vls; struct pio_vl_map** map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pio_vl_map*) ; 

__attribute__((used)) static void pio_map_free(struct pio_vl_map *m)
{
	int i;

	for (i = 0; m && i < m->actual_vls; i++)
		kfree(m->map[i]);
	kfree(m);
}
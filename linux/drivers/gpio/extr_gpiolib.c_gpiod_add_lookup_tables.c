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
struct gpiod_lookup_table {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_lookup_list ; 
 int /*<<< orphan*/  gpio_lookup_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gpiod_add_lookup_tables(struct gpiod_lookup_table **tables, size_t n)
{
	unsigned int i;

	mutex_lock(&gpio_lookup_lock);

	for (i = 0; i < n; i++)
		list_add_tail(&tables[i]->list, &gpio_lookup_list);

	mutex_unlock(&gpio_lookup_lock);
}
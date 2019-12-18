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
struct gpiod_lookup_table {struct gpiod_lookup* table; } ;
struct gpiod_lookup {scalar_t__ con_id; scalar_t__ chip_label; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct gpiod_lookup_table* gpiod_find_lookup_table (struct device*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int platform_gpio_count(struct device *dev, const char *con_id)
{
	struct gpiod_lookup_table *table;
	struct gpiod_lookup *p;
	unsigned int count = 0;

	table = gpiod_find_lookup_table(dev);
	if (!table)
		return -ENOENT;

	for (p = &table->table[0]; p->chip_label; p++) {
		if ((con_id && p->con_id && !strcmp(con_id, p->con_id)) ||
		    (!con_id && !p->con_id))
			count++;
	}
	if (!count)
		return -ENOENT;

	return count;
}
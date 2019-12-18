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
typedef  int /*<<< orphan*/  u8 ;
struct sja1105_table {int entry_count; int /*<<< orphan*/ * entries; TYPE_1__* ops; } ;
struct TYPE_2__ {size_t unpacked_entry_size; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int sja1105_table_delete_entry(struct sja1105_table *table, int i)
{
	size_t entry_size = table->ops->unpacked_entry_size;
	u8 *entries = table->entries;

	if (i > table->entry_count)
		return -ERANGE;

	memmove(entries + i * entry_size, entries + (i + 1) * entry_size,
		(table->entry_count - i) * entry_size);

	table->entry_count--;

	return 0;
}
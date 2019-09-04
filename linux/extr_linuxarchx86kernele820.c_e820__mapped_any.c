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
typedef  scalar_t__ u64 ;
struct e820_entry {int type; scalar_t__ addr; scalar_t__ size; } ;
typedef  enum e820_type { ____Placeholder_e820_type } e820_type ;
struct TYPE_2__ {int nr_entries; struct e820_entry* entries; } ;

/* Variables and functions */
 TYPE_1__* e820_table ; 

bool e820__mapped_any(u64 start, u64 end, enum e820_type type)
{
	int i;

	for (i = 0; i < e820_table->nr_entries; i++) {
		struct e820_entry *entry = &e820_table->entries[i];

		if (type && entry->type != type)
			continue;
		if (entry->addr >= end || entry->addr + entry->size <= start)
			continue;
		return 1;
	}
	return 0;
}
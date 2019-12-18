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
struct TYPE_2__ {void* context; } ;
struct dm_array_info {TYPE_1__ value_type; } ;
struct array_block {int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 void const* element_at (struct dm_array_info*,struct array_block*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_entries(struct dm_array_info *info, struct array_block *ab,
		       void (*fn)(void *, const void *))
{
	unsigned i, nr_entries = le32_to_cpu(ab->nr_entries);

	for (i = 0; i < nr_entries; i++)
		fn(info->value_type.context, element_at(info, ab, i));
}
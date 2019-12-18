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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct uni_table_desc {int /*<<< orphan*/  entry_size; int /*<<< orphan*/  findex; int /*<<< orphan*/  num_entries; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct uni_table_desc *qlcnic_get_table_desc(const u8 *unirom, int section)
{
	u32 i, entries;
	struct uni_table_desc *directory = (struct uni_table_desc *) &unirom[0];
	entries = le32_to_cpu(directory->num_entries);

	for (i = 0; i < entries; i++) {

		u32 offs = le32_to_cpu(directory->findex) +
			   i * le32_to_cpu(directory->entry_size);
		u32 tab_type = le32_to_cpu(*((__le32 *)&unirom[offs] + 8));

		if (tab_type == section)
			return (struct uni_table_desc *) &unirom[offs];
	}

	return NULL;
}
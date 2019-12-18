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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct uni_table_desc {int /*<<< orphan*/  entry_size; int /*<<< orphan*/  findex; int /*<<< orphan*/  num_entries; } ;
typedef  size_t __le32 ;

/* Variables and functions */
 size_t cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uni_table_desc *nx_get_table_desc(const u8 *unirom, int section)
{
	uint32_t i;
	struct uni_table_desc *directory = (struct uni_table_desc *) &unirom[0];
	__le32 entries = cpu_to_le32(directory->num_entries);

	for (i = 0; i < entries; i++) {

		__le32 offs = cpu_to_le32(directory->findex) +
				(i * cpu_to_le32(directory->entry_size));
		__le32 tab_type = cpu_to_le32(*((u32 *)&unirom[offs] + 8));

		if (tab_type == section)
			return (struct uni_table_desc *) &unirom[offs];
	}

	return NULL;
}
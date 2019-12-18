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
struct dm_clone_metadata {int /*<<< orphan*/  bitset_root; int /*<<< orphan*/  bitset_info; int /*<<< orphan*/  region_map; int /*<<< orphan*/  nr_regions; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int dm_bitset_set_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __update_metadata_word(struct dm_clone_metadata *cmd, unsigned long word)
{
	int r;
	unsigned long index = word * BITS_PER_LONG;
	unsigned long max_index = min(cmd->nr_regions, (word + 1) * BITS_PER_LONG);

	while (index < max_index) {
		if (test_bit(index, cmd->region_map)) {
			r = dm_bitset_set_bit(&cmd->bitset_info, cmd->bitset_root,
					      index, &cmd->bitset_root);

			if (r) {
				DMERR("dm_bitset_set_bit failed");
				return r;
			}
		}
		index++;
	}

	return 0;
}
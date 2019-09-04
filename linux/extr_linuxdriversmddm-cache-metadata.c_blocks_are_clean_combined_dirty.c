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
struct dm_cache_metadata {int dummy; } ;
typedef  scalar_t__ dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int block_clean_combined_dirty (struct dm_cache_metadata*,scalar_t__,int*) ; 
 scalar_t__ from_cblock (scalar_t__) ; 
 scalar_t__ to_cblock (scalar_t__) ; 

__attribute__((used)) static int blocks_are_clean_combined_dirty(struct dm_cache_metadata *cmd,
					   dm_cblock_t begin, dm_cblock_t end,
					   bool *result)
{
	int r;
	*result = true;

	while (begin != end) {
		r = block_clean_combined_dirty(cmd, begin, result);
		if (r) {
			DMERR("block_clean_combined_dirty failed");
			return r;
		}

		if (!*result) {
			DMERR("cache block %llu is dirty",
			      (unsigned long long) from_cblock(begin));
			return 0;
		}

		begin = to_cblock(from_cblock(begin) + 1);
	}

	return 0;
}
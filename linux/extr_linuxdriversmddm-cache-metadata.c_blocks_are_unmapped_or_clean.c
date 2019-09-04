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
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int blocks_are_clean_combined_dirty (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int blocks_are_clean_separate_dirty (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 

__attribute__((used)) static int blocks_are_unmapped_or_clean(struct dm_cache_metadata *cmd,
					dm_cblock_t begin, dm_cblock_t end,
					bool *result)
{
	if (separate_dirty_bits(cmd))
		return blocks_are_clean_separate_dirty(cmd, begin, end, result);
	else
		return blocks_are_clean_combined_dirty(cmd, begin, end, result);
}
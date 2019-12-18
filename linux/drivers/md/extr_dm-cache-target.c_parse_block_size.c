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
struct dm_arg_set {int dummy; } ;
struct cache_args {unsigned long cache_sectors; unsigned long block_size; } ;

/* Variables and functions */
 unsigned long DATA_DEV_BLOCK_SIZE_MAX_SECTORS ; 
 unsigned long DATA_DEV_BLOCK_SIZE_MIN_SECTORS ; 
 int EINVAL ; 
 int /*<<< orphan*/  at_least_one_arg (struct dm_arg_set*,char**) ; 
 int /*<<< orphan*/  dm_shift_arg (struct dm_arg_set*) ; 
 scalar_t__ kstrtoul (int /*<<< orphan*/ ,int,unsigned long*) ; 

__attribute__((used)) static int parse_block_size(struct cache_args *ca, struct dm_arg_set *as,
			    char **error)
{
	unsigned long block_size;

	if (!at_least_one_arg(as, error))
		return -EINVAL;

	if (kstrtoul(dm_shift_arg(as), 10, &block_size) || !block_size ||
	    block_size < DATA_DEV_BLOCK_SIZE_MIN_SECTORS ||
	    block_size > DATA_DEV_BLOCK_SIZE_MAX_SECTORS ||
	    block_size & (DATA_DEV_BLOCK_SIZE_MIN_SECTORS - 1)) {
		*error = "Invalid data block size";
		return -EINVAL;
	}

	if (block_size > ca->cache_sectors) {
		*error = "Data block size is larger than the cache device";
		return -EINVAL;
	}

	ca->block_size = block_size;

	return 0;
}
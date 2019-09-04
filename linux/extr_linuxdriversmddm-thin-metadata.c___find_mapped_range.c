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
struct dm_thin_lookup_result {scalar_t__ block; int shared; } ;
struct dm_thin_device {int dummy; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 int __find_block (struct dm_thin_device*,scalar_t__,int,struct dm_thin_lookup_result*) ; 
 int __find_next_mapped_block (struct dm_thin_device*,scalar_t__,scalar_t__*,struct dm_thin_lookup_result*) ; 

__attribute__((used)) static int __find_mapped_range(struct dm_thin_device *td,
			       dm_block_t begin, dm_block_t end,
			       dm_block_t *thin_begin, dm_block_t *thin_end,
			       dm_block_t *pool_begin, bool *maybe_shared)
{
	int r;
	dm_block_t pool_end;
	struct dm_thin_lookup_result lookup;

	if (end < begin)
		return -ENODATA;

	r = __find_next_mapped_block(td, begin, &begin, &lookup);
	if (r)
		return r;

	if (begin >= end)
		return -ENODATA;

	*thin_begin = begin;
	*pool_begin = lookup.block;
	*maybe_shared = lookup.shared;

	begin++;
	pool_end = *pool_begin + 1;
	while (begin != end) {
		r = __find_block(td, begin, true, &lookup);
		if (r) {
			if (r == -ENODATA)
				break;
			else
				return r;
		}

		if ((lookup.block != pool_end) ||
		    (lookup.shared != *maybe_shared))
			break;

		pool_end++;
		begin++;
	}

	*thin_end = begin;
	return 0;
}
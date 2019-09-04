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

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int __set_dirty_bits_v1 (struct dm_cache_metadata*,unsigned int,unsigned long*) ; 
 int __set_dirty_bits_v2 (struct dm_cache_metadata*,unsigned int,unsigned long*) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 

int dm_cache_set_dirty_bits(struct dm_cache_metadata *cmd,
			    unsigned nr_bits,
			    unsigned long *bits)
{
	int r;

	WRITE_LOCK(cmd);
	if (separate_dirty_bits(cmd))
		r = __set_dirty_bits_v2(cmd, nr_bits, bits);
	else
		r = __set_dirty_bits_v1(cmd, nr_bits, bits);
	WRITE_UNLOCK(cmd);

	return r;
}
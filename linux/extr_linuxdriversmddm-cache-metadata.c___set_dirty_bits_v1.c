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
 int __dirty (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  to_cblock (unsigned int) ; 

__attribute__((used)) static int __set_dirty_bits_v1(struct dm_cache_metadata *cmd, unsigned nr_bits, unsigned long *bits)
{
	int r;
	unsigned i;
	for (i = 0; i < nr_bits; i++) {
		r = __dirty(cmd, to_cblock(i), test_bit(i, bits));
		if (r)
			return r;
	}

	return 0;
}
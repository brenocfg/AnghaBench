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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS ; 
 scalar_t__ IS_ALIGNED (unsigned long,int) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ __be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_to_be64 (scalar_t__) ; 

__attribute__((used)) static void cc_update_ctr(u8 *ctr, unsigned int increment)
{
	if (IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) ||
	    IS_ALIGNED((unsigned long)ctr, 8)) {

		__be64 *high_be = (__be64 *)ctr;
		__be64 *low_be = high_be + 1;
		u64 orig_low = __be64_to_cpu(*low_be);
		u64 new_low = orig_low + (u64)increment;

		*low_be = __cpu_to_be64(new_low);

		if (new_low < orig_low)
			*high_be = __cpu_to_be64(__be64_to_cpu(*high_be) + 1);
	} else {
		u8 *pos = (ctr + AES_BLOCK_SIZE);
		u8 val;
		unsigned int size;

		for (; increment; increment--)
			for (size = AES_BLOCK_SIZE; size; size--) {
				val = *--pos + 1;
				*pos = val;
				if (val)
					break;
			}
	}
}
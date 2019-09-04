#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int cbm_len; } ;
struct rdt_resource {TYPE_1__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (unsigned long*,unsigned long,unsigned int) ; 
 unsigned long find_first_bit (unsigned long*,unsigned int) ; 
 unsigned long find_next_zero_bit (unsigned long*,unsigned int,unsigned long) ; 

__attribute__((used)) static void cbm_ensure_valid(u32 *_val, struct rdt_resource *r)
{
	/*
	 * Convert the u32 _val to an unsigned long required by all the bit
	 * operations within this function. No more than 32 bits of this
	 * converted value can be accessed because all bit operations are
	 * additionally provided with cbm_len that is initialized during
	 * hardware enumeration using five bits from the EAX register and
	 * thus never can exceed 32 bits.
	 */
	unsigned long *val = (unsigned long *)_val;
	unsigned int cbm_len = r->cache.cbm_len;
	unsigned long first_bit, zero_bit;

	if (*val == 0)
		return;

	first_bit = find_first_bit(val, cbm_len);
	zero_bit = find_next_zero_bit(val, cbm_len, first_bit);

	/* Clear any remaining bits to ensure contiguous region */
	bitmap_clear(val, zero_bit, cbm_len - zero_bit);
}
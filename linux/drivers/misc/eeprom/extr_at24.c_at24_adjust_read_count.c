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
struct at24_data {int flags; } ;

/* Variables and functions */
 int AT24_FLAG_ADDR16 ; 
 int AT24_FLAG_NO_RDROL ; 
 unsigned int BIT (unsigned int) ; 
 size_t at24_io_limit ; 

__attribute__((used)) static size_t at24_adjust_read_count(struct at24_data *at24,
				      unsigned int offset, size_t count)
{
	unsigned int bits;
	size_t remainder;

	/*
	 * In case of multi-address chips that don't rollover reads to
	 * the next slave address: truncate the count to the slave boundary,
	 * so that the read never straddles slaves.
	 */
	if (at24->flags & AT24_FLAG_NO_RDROL) {
		bits = (at24->flags & AT24_FLAG_ADDR16) ? 16 : 8;
		remainder = BIT(bits) - offset;
		if (count > remainder)
			count = remainder;
	}

	if (count > at24_io_limit)
		count = at24_io_limit;

	return count;
}
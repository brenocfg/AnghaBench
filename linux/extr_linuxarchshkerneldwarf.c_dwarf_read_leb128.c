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
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 unsigned char __raw_readb (char*) ; 

__attribute__((used)) static inline unsigned long dwarf_read_leb128(char *addr, int *ret)
{
	unsigned char byte;
	int result, shift;
	int num_bits;
	int count;

	result = 0;
	shift = 0;
	count = 0;

	while (1) {
		byte = __raw_readb(addr);
		addr++;
		result |= (byte & 0x7f) << shift;
		shift += 7;
		count++;

		if (!(byte & 0x80))
			break;
	}

	/* The number of bits in a signed integer. */
	num_bits = 8 * sizeof(result);

	if ((shift < num_bits) && (byte & 0x40))
		result |= (-1 << shift);

	*ret = result;

	return count;
}
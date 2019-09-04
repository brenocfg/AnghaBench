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

/* Variables and functions */
 unsigned char __raw_readb (char*) ; 

__attribute__((used)) static inline unsigned long dwarf_read_uleb128(char *addr, unsigned int *ret)
{
	unsigned int result;
	unsigned char byte;
	int shift, count;

	result = 0;
	shift = 0;
	count = 0;

	while (1) {
		byte = __raw_readb(addr);
		addr++;
		count++;

		result |= (byte & 0x7f) << shift;
		shift += 7;

		if (!(byte & 0x80))
			break;
	}

	*ret = result;

	return count;
}
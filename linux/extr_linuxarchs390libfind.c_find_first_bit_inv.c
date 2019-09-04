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
 int BITS_PER_LONG ; 
 int __fls (unsigned long) ; 

unsigned long find_first_bit_inv(const unsigned long *addr, unsigned long size)
{
	const unsigned long *p = addr;
	unsigned long result = 0;
	unsigned long tmp;

	while (size & ~(BITS_PER_LONG - 1)) {
		if ((tmp = *(p++)))
			goto found;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	}
	if (!size)
		return result;
	tmp = (*p) & (~0UL << (BITS_PER_LONG - size));
	if (!tmp)		/* Are any bits set? */
		return result + size;	/* Nope. */
found:
	return result + (__fls(tmp) ^ (BITS_PER_LONG - 1));
}
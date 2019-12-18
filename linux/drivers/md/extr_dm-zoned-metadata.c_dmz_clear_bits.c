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
 int BIT_WORD (int) ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ test_and_clear_bit (int,unsigned long*) ; 

__attribute__((used)) static int dmz_clear_bits(unsigned long *bitmap, int bit, int nr_bits)
{
	unsigned long *addr;
	int end = bit + nr_bits;
	int n = 0;

	while (bit < end) {
		if (((bit & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PER_LONG)) {
			/* Try to clear whole word at once */
			addr = bitmap + BIT_WORD(bit);
			if (*addr == ULONG_MAX) {
				*addr = 0;
				n += BITS_PER_LONG;
				bit += BITS_PER_LONG;
				continue;
			}
		}

		if (test_and_clear_bit(bit, bitmap))
			n++;
		bit++;
	}

	return n;
}
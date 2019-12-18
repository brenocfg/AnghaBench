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
 int BIT_WORD (unsigned int) ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static unsigned int dmz_set_bits(unsigned long *bitmap,
				 unsigned int bit, unsigned int nr_bits)
{
	unsigned long *addr;
	unsigned int end = bit + nr_bits;
	unsigned int n = 0;

	while (bit < end) {
		if (((bit & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PER_LONG)) {
			/* Try to set the whole word at once */
			addr = bitmap + BIT_WORD(bit);
			if (*addr == 0) {
				*addr = ULONG_MAX;
				n += BITS_PER_LONG;
				bit += BITS_PER_LONG;
				continue;
			}
		}

		if (!test_and_set_bit(bit, bitmap))
			n++;
		bit++;
	}

	return n;
}
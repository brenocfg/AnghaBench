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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 unsigned long GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 unsigned long cmpxchg (unsigned long volatile*,unsigned long,unsigned long) ; 

unsigned long __cmpxchg_small(volatile void *ptr, unsigned long old,
			      unsigned long new, unsigned int size)
{
	u32 mask, old32, new32, load32, load;
	volatile u32 *ptr32;
	unsigned int shift;

	/* Check that ptr is naturally aligned */
	WARN_ON((unsigned long)ptr & (size - 1));

	/* Mask inputs to the correct size. */
	mask = GENMASK((size * BITS_PER_BYTE) - 1, 0);
	old &= mask;
	new &= mask;

	/*
	 * Calculate a shift & mask that correspond to the value we wish to
	 * compare & exchange within the naturally aligned 4 byte integer
	 * that includes it.
	 */
	shift = (unsigned long)ptr & 0x3;
	if (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		shift ^= sizeof(u32) - size;
	shift *= BITS_PER_BYTE;
	mask <<= shift;

	/*
	 * Calculate a pointer to the naturally aligned 4 byte integer that
	 * includes our byte of interest, and load its value.
	 */
	ptr32 = (volatile u32 *)((unsigned long)ptr & ~0x3);
	load32 = *ptr32;

	while (true) {
		/*
		 * Ensure the byte we want to exchange matches the expected
		 * old value, and if not then bail.
		 */
		load = (load32 & mask) >> shift;
		if (load != old)
			return load;

		/*
		 * Calculate the old & new values of the naturally aligned
		 * 4 byte integer that include the byte we want to exchange.
		 * Attempt to exchange the old value for the new value, and
		 * return if we succeed.
		 */
		old32 = (load32 & ~mask) | (old << shift);
		new32 = (load32 & ~mask) | (new << shift);
		load32 = cmpxchg(ptr32, old32, new32);
		if (load32 == old32)
			return old;
	}
}
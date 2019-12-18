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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fls (int) ; 
 int* logtable ; 
 scalar_t__ unlikely (int) ; 

unsigned int intlog2(u32 value)
{
	/**
	 *	returns: log2(value) * 2^24
	 *	wrong result if value = 0 (log2(0) is undefined)
	 */
	unsigned int msb;
	unsigned int logentry;
	unsigned int significand;
	unsigned int interpolation;

	if (unlikely(value == 0)) {
		WARN_ON(1);
		return 0;
	}

	/* first detect the msb (count begins at 0) */
	msb = fls(value) - 1;

	/**
	 *	now we use a logtable after the following method:
	 *
	 *	log2(2^x * y) * 2^24 = x * 2^24 + log2(y) * 2^24
	 *	where x = msb and therefore 1 <= y < 2
	 *	first y is determined by shifting the value left
	 *	so that msb is bit 31
	 *		0x00231f56 -> 0x8C7D5800
	 *	the result is y * 2^31 -> "significand"
	 *	then the highest 9 bits are used for a table lookup
	 *	the highest bit is discarded because it's always set
	 *	the highest nine bits in our example are 100011000
	 *	so we would use the entry 0x18
	 */
	significand = value << (31 - msb);
	logentry = (significand >> 23) & 0xff;

	/**
	 *	last step we do is interpolation because of the
	 *	limitations of the log table the error is that part of
	 *	the significand which isn't used for lookup then we
	 *	compute the ratio between the error and the next table entry
	 *	and interpolate it between the log table entry used and the
	 *	next one the biggest error possible is 0x7fffff
	 *	(in our example it's 0x7D5800)
	 *	needed value for next table entry is 0x800000
	 *	so the interpolation is
	 *	(error / 0x800000) * (logtable_next - logtable_current)
	 *	in the implementation the division is moved to the end for
	 *	better accuracy there is also an overflow correction if
	 *	logtable_next is 256
	 */
	interpolation = ((significand & 0x7fffff) *
			((logtable[(logentry + 1) & 0xff] -
			  logtable[logentry]) & 0xffff)) >> 15;

	/* now we return the result */
	return ((msb << 24) + (logtable[logentry] << 8) + interpolation);
}
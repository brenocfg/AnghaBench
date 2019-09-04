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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long get_cycles () ; 
 int /*<<< orphan*/  pit_verify_msb (unsigned char) ; 

__attribute__((used)) static inline int pit_expect_msb(unsigned char val, u64 *tscp, unsigned long *deltap)
{
	int count;
	u64 tsc = 0, prev_tsc = 0;

	for (count = 0; count < 50000; count++) {
		if (!pit_verify_msb(val))
			break;
		prev_tsc = tsc;
		tsc = get_cycles();
	}
	*deltap = get_cycles() - prev_tsc;
	*tscp = tsc;

	/*
	 * We require _some_ success, but the quality control
	 * will be based on the error terms on the TSC values.
	 */
	return count > 5;
}
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
typedef  unsigned long long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  AD9834_FREQ_BITS ; 
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static unsigned int ad9834_calc_freqreg(unsigned long mclk, unsigned long fout)
{
	unsigned long long freqreg = (u64)fout * (u64)BIT(AD9834_FREQ_BITS);

	do_div(freqreg, mclk);
	return freqreg;
}
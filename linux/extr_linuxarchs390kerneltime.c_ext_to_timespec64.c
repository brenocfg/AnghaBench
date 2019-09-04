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
struct timespec64 {unsigned long long tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */
 unsigned long long do_div (unsigned long long,int) ; 

__attribute__((used)) static void ext_to_timespec64(unsigned char *clk, struct timespec64 *xt)
{
	unsigned long long high, low, rem, sec, nsec;

	/* Split extendnd TOD clock to micro-seconds and sub-micro-seconds */
	high = (*(unsigned long long *) clk) >> 4;
	low = (*(unsigned long long *)&clk[7]) << 4;
	/* Calculate seconds and nano-seconds */
	sec = high;
	rem = do_div(sec, 1000000);
	nsec = (((low >> 32) + (rem << 32)) * 1000) >> 32;

	xt->tv_sec = sec;
	xt->tv_nsec = nsec;
}
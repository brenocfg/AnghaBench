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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static unsigned long
calc_rate(unsigned long rate, u32 m, u32 n, u32 mode, u32 pre_div)
{
	if (pre_div)
		rate /= pre_div + 1;

	if (mode) {
		u64 tmp = rate;
		tmp *= m;
		do_div(tmp, n);
		rate = tmp;
	}

	return rate;
}
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
struct rapl_package {int time_unit; } ;

/* Variables and functions */
 int div64_u64 (int,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int ilog2 (int) ; 

__attribute__((used)) static u64 rapl_compute_time_window_core(struct rapl_package *rp, u64 value,
					 bool to_raw)
{
	u64 f, y;		/* fraction and exp. used for time unit */

	/*
	 * Special processing based on 2^Y*(1+F/4), refer
	 * to Intel Software Developer's manual Vol.3B: CH 14.9.3.
	 */
	if (!to_raw) {
		f = (value & 0x60) >> 5;
		y = value & 0x1f;
		value = (1 << y) * (4 + f) * rp->time_unit / 4;
	} else {
		do_div(value, rp->time_unit);
		y = ilog2(value);
		f = div64_u64(4 * (value - (1 << y)), 1 << y);
		value = (y & 0x1f) | ((f & 0x3) << 5);
	}
	return value;
}
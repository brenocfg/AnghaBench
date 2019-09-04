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
 int BIT (int) ; 
 int BPAR ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 calc_reg(u32 parent_rate, u32 rate)
{
	u32 sel, integ, fra_div, tmp;
	u64 tmp64 = (u64)parent_rate * BPAR;

	do_div(tmp64, rate);
	integ = (u32)tmp64 / BPAR;
	integ = integ >> 1;

	tmp = (u32)tmp64 % BPAR;
	sel = tmp / BPAR;

	tmp = tmp % BPAR;
	fra_div = tmp * 0xff / BPAR;
	tmp = (sel << 24) | (integ << 16) | (0xff << 8) | fra_div;

	/* Set I2S integer divider as 1. This bit is reserved for SPDIF
	 * and do no harm.
	 */
	tmp |= BIT(28);
	return tmp;
}
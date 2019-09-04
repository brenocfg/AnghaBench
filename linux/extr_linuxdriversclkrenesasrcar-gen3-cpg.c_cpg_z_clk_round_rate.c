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
typedef  unsigned int u64 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 unsigned int div_u64 (unsigned long,unsigned long) ; 

__attribute__((used)) static long cpg_z_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *parent_rate)
{
	/* Factor of 2 is for fixed divider */
	unsigned long prate = *parent_rate / 2;
	unsigned int mult;

	mult = div_u64(rate * 32ULL, prate);
	mult = clamp(mult, 1U, 32U);

	return (u64)prate * mult / 32;
}
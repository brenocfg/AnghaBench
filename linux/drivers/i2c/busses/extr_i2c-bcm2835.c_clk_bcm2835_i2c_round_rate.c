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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bcm2835_i2c_calc_divider (unsigned long,unsigned long) ; 

__attribute__((used)) static long clk_bcm2835_i2c_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *parent_rate)
{
	u32 divider = clk_bcm2835_i2c_calc_divider(rate, *parent_rate);

	return DIV_ROUND_UP(*parent_rate, divider);
}
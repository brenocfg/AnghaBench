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
typedef  int u8 ;
typedef  int u32 ;
struct s3c24xx_clkout {int shift; int mask; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S3C24XX_MISCCR ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct s3c24xx_clkout* to_s3c24xx_clkout (struct clk_hw*) ; 

__attribute__((used)) static u8 s3c24xx_clkout_get_parent(struct clk_hw *hw)
{
	struct s3c24xx_clkout *clkout = to_s3c24xx_clkout(hw);
	int num_parents = clk_hw_get_num_parents(hw);
	u32 val;

	val = readl_relaxed(S3C24XX_MISCCR) >> clkout->shift;
	val >>= clkout->shift;
	val &= clkout->mask;

	if (val >= num_parents)
		return -EINVAL;

	return val;
}
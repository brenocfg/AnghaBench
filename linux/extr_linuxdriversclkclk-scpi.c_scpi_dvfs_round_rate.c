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
struct scpi_clk {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long __scpi_dvfs_round_rate (struct scpi_clk*,unsigned long) ; 
 struct scpi_clk* to_scpi_clk (struct clk_hw*) ; 

__attribute__((used)) static long scpi_dvfs_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *parent_rate)
{
	struct scpi_clk *clk = to_scpi_clk(hw);

	return __scpi_dvfs_round_rate(clk, rate);
}
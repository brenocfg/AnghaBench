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
typedef  enum gpmc_clk_domain { ____Placeholder_gpmc_clk_domain } gpmc_clk_domain ;

/* Variables and functions */
 unsigned int gpmc_get_clk_period (int,int) ; 

__attribute__((used)) static unsigned int gpmc_clk_ticks_to_ns(unsigned int ticks, int cs,
					 enum gpmc_clk_domain cd)
{
	return ticks * gpmc_get_clk_period(cs, cd) / 1000;
}
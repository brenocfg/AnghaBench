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
 unsigned long gpmc_get_clk_period (int,int) ; 

__attribute__((used)) static unsigned int gpmc_ns_to_clk_ticks(unsigned int time_ns, int cs,
					 enum gpmc_clk_domain cd)
{
	unsigned long tick_ps;

	/* Calculate in picosecs to yield more exact results */
	tick_ps = gpmc_get_clk_period(cs, cd);

	return (time_ns * 1000 + tick_ps - 1) / tick_ps;
}
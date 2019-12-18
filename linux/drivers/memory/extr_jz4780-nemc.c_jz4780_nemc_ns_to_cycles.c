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
typedef  int uint32_t ;
struct jz4780_nemc {int clk_period; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t jz4780_nemc_ns_to_cycles(struct jz4780_nemc *nemc, uint32_t ns)
{
	return ((ns * 1000) + nemc->clk_period - 1) / nemc->clk_period;
}
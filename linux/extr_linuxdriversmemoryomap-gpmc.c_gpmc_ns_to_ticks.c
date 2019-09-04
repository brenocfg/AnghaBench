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

/* Variables and functions */
 int /*<<< orphan*/  GPMC_CD_FCLK ; 
 unsigned int gpmc_ns_to_clk_ticks (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int gpmc_ns_to_ticks(unsigned int time_ns)
{
	return gpmc_ns_to_clk_ticks(time_ns, /* any CS */ 0, GPMC_CD_FCLK);
}
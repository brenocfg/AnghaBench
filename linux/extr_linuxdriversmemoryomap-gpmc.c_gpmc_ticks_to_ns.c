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
 unsigned int gpmc_clk_ticks_to_ns (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int gpmc_ticks_to_ns(unsigned int ticks)
{
	return gpmc_clk_ticks_to_ns(ticks, /* any CS */ 0, GPMC_CD_FCLK);
}
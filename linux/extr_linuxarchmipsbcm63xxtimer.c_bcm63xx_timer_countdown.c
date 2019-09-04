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
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_clk ; 

unsigned int bcm63xx_timer_countdown(unsigned int countdown_us)
{
	return (clk_get_rate(periph_clk) / (1000 * 1000)) * countdown_us;
}
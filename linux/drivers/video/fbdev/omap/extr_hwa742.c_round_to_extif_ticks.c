#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int extif_clk_period; } ;

/* Variables and functions */
 TYPE_1__ hwa742 ; 

__attribute__((used)) static unsigned long round_to_extif_ticks(unsigned long ps, int div)
{
	int bus_tick = hwa742.extif_clk_period * div;
	return (ps + bus_tick - 1) / bus_tick * bus_tick;
}
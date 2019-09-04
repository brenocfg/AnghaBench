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
struct dispc_device {unsigned long core_clk_rate; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long dispc_core_clk_rate(struct dispc_device *dispc)
{
	return dispc->core_clk_rate;
}
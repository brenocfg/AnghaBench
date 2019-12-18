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
struct intel_dsi {int escape_clk_div; } ;

/* Variables and functions */

int intel_dsi_tlpx_ns(const struct intel_dsi *intel_dsi)
{
	switch (intel_dsi->escape_clk_div) {
	default:
	case 0:
		return 50;
	case 1:
		return 100;
	case 2:
		return 200;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clkdco; } ;
struct TYPE_4__ {TYPE_1__ cinfo; } ;
struct dsi_data {TYPE_2__ pll; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ns2ddr(struct dsi_data *dsi, unsigned int ns)
{
	/* convert time in ns to ddr ticks, rounding up */
	unsigned long ddr_clk = dsi->pll.cinfo.clkdco / 4;

	return (ns * (ddr_clk / 1000 / 1000) + 999) / 1000;
}
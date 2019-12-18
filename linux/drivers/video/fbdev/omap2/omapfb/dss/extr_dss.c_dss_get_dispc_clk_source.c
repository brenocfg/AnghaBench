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
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
struct TYPE_2__ {int dispc_clk_source; } ;

/* Variables and functions */
 TYPE_1__ dss ; 

enum omap_dss_clk_source dss_get_dispc_clk_source(void)
{
	return dss.dispc_clk_source;
}
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
struct dce8_wm_params {int num_heads; } ;

/* Variables and functions */
 int dce_v8_0_average_bandwidth (struct dce8_wm_params*) ; 
 int dce_v8_0_dram_bandwidth_for_display (struct dce8_wm_params*) ; 

__attribute__((used)) static bool dce_v8_0_average_bandwidth_vs_dram_bandwidth_for_display(struct dce8_wm_params *wm)
{
	if (dce_v8_0_average_bandwidth(wm) <=
	    (dce_v8_0_dram_bandwidth_for_display(wm) / wm->num_heads))
		return true;
	else
		return false;
}
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
struct intel_dp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t skl_get_aux_clock_divider(struct intel_dp *intel_dp, int index)
{
	/*
	 * SKL doesn't need us to program the AUX clock divider (Hardware will
	 * derive the clock from CDCLK automatically). We still implement the
	 * get_aux_clock_divider vfunc to plug-in into the existing code.
	 */
	return index ? 0 : 1;
}
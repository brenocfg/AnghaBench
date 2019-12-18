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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_disable_sram_shut_down (struct dce_hwseq*) ; 
 int /*<<< orphan*/  dce_underlay_clock_enable (struct dce_hwseq*) ; 
 int /*<<< orphan*/  disable_sw_manual_control_light_sleep () ; 
 int /*<<< orphan*/  enable_hw_base_light_sleep () ; 

void dce_clock_gating_power_up(struct dce_hwseq *hws,
		bool enable)
{
	if (enable) {
		enable_hw_base_light_sleep();
		disable_sw_manual_control_light_sleep();
	} else {
		dce_disable_sram_shut_down(hws);
		dce_underlay_clock_enable(hws);
	}
}
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
struct TYPE_2__ {int /*<<< orphan*/  pplib_apply_display_requirements; int /*<<< orphan*/  set_bandwidth; int /*<<< orphan*/  enable_display_power_gating; } ;
struct dc {TYPE_1__ hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce100_enable_display_power_gating ; 
 int /*<<< orphan*/  dce100_pplib_apply_display_requirements ; 
 int /*<<< orphan*/  dce100_set_bandwidth ; 
 int /*<<< orphan*/  dce110_hw_sequencer_construct (struct dc*) ; 

void dce100_hw_sequencer_construct(struct dc *dc)
{
	dce110_hw_sequencer_construct(dc);

	dc->hwss.enable_display_power_gating = dce100_enable_display_power_gating;
	dc->hwss.set_bandwidth = dce100_set_bandwidth;
	dc->hwss.pplib_apply_display_requirements =
			dce100_pplib_apply_display_requirements;
}
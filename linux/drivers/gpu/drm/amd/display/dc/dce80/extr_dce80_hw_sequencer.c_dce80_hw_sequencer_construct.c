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
struct TYPE_2__ {int /*<<< orphan*/  optimize_bandwidth; int /*<<< orphan*/  prepare_bandwidth; int /*<<< orphan*/  pipe_control_lock; int /*<<< orphan*/  enable_display_power_gating; } ;
struct dc {TYPE_1__ hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce100_enable_display_power_gating ; 
 int /*<<< orphan*/  dce100_optimize_bandwidth ; 
 int /*<<< orphan*/  dce100_prepare_bandwidth ; 
 int /*<<< orphan*/  dce110_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/  dce_pipe_control_lock ; 

void dce80_hw_sequencer_construct(struct dc *dc)
{
	dce110_hw_sequencer_construct(dc);

	dc->hwss.enable_display_power_gating = dce100_enable_display_power_gating;
	dc->hwss.pipe_control_lock = dce_pipe_control_lock;
	dc->hwss.prepare_bandwidth = dce100_prepare_bandwidth;
	dc->hwss.optimize_bandwidth = dce100_optimize_bandwidth;
}
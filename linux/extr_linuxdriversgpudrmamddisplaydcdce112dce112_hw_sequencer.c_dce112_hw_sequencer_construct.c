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
struct TYPE_2__ {int /*<<< orphan*/  enable_display_power_gating; } ;
struct dc {TYPE_1__ hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/  dce112_enable_display_power_gating ; 

void dce112_hw_sequencer_construct(struct dc *dc)
{
	/* All registers used by dce11.2 match those in dce11 in offset and
	 * structure
	 */
	dce110_hw_sequencer_construct(dc);
	dc->hwss.enable_display_power_gating = dce112_enable_display_power_gating;
}
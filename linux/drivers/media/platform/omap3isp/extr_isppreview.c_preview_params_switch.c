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
typedef  int u32 ;
struct TYPE_4__ {int active; TYPE_1__* params; } ;
struct isp_prev_device {TYPE_2__ params; } ;
struct TYPE_3__ {int update; int busy; } ;

/* Variables and functions */

__attribute__((used)) static void preview_params_switch(struct isp_prev_device *prev)
{
	u32 to_switch;

	/* Switch active parameters with updated shadow parameters when the
	 * shadow parameter has been updated and neither the active not the
	 * shadow parameter is busy.
	 */
	to_switch = (prev->params.params[0].update & ~prev->params.active)
		  | (prev->params.params[1].update & prev->params.active);
	to_switch &= ~(prev->params.params[0].busy |
		       prev->params.params[1].busy);
	if (to_switch == 0)
		return;

	prev->params.active ^= to_switch;

	/* Remove the update flag for the shadow copy of parameters we have
	 * switched.
	 */
	prev->params.params[0].update &= ~(~prev->params.active & to_switch);
	prev->params.params[1].update &= ~(prev->params.active & to_switch);
}
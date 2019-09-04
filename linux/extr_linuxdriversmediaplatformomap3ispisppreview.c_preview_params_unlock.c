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

__attribute__((used)) static void
preview_params_unlock(struct isp_prev_device *prev, u32 update, bool shadow)
{
	u32 active = prev->params.active;

	if (shadow) {
		/* Set the update flag for shadow parameters that have been
		 * updated and clear the busy flag for all shadow parameters.
		 */
		prev->params.params[0].update |= (~active & update);
		prev->params.params[1].update |= (active & update);
		prev->params.params[0].busy &= active;
		prev->params.params[1].busy &= ~active;
	} else {
		/* Clear the update flag for active parameters that have been
		 * applied and the busy flag for all active parameters.
		 */
		prev->params.params[0].update &= ~(active & update);
		prev->params.params[1].update &= ~(~active & update);
		prev->params.params[0].busy &= ~active;
		prev->params.params[1].busy &= active;
	}
}
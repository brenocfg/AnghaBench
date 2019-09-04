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
struct TYPE_3__ {int busy; int update; } ;

/* Variables and functions */

__attribute__((used)) static u32
preview_params_lock(struct isp_prev_device *prev, u32 update, bool shadow)
{
	u32 active = prev->params.active;

	if (shadow) {
		/* Mark all shadow parameters we are going to touch as busy. */
		prev->params.params[0].busy |= ~active & update;
		prev->params.params[1].busy |= active & update;
	} else {
		/* Mark all active parameters we are going to touch as busy. */
		update = (prev->params.params[0].update & active)
		       | (prev->params.params[1].update & ~active);

		prev->params.params[0].busy |= active & update;
		prev->params.params[1].busy |= ~active & update;
	}

	return update;
}
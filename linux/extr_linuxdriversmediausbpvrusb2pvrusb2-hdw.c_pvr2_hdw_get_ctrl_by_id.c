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
struct pvr2_hdw {unsigned int control_cnt; struct pvr2_ctrl* controls; } ;
struct pvr2_ctrl {TYPE_1__* info; } ;
struct TYPE_2__ {int internal_id; } ;

/* Variables and functions */

struct pvr2_ctrl *pvr2_hdw_get_ctrl_by_id(struct pvr2_hdw *hdw,
					  unsigned int ctl_id)
{
	struct pvr2_ctrl *cptr;
	unsigned int idx;
	int i;

	/* This could be made a lot more efficient, but for now... */
	for (idx = 0; idx < hdw->control_cnt; idx++) {
		cptr = hdw->controls + idx;
		i = cptr->info->internal_id;
		if (i && (i == ctl_id)) return cptr;
	}
	return NULL;
}
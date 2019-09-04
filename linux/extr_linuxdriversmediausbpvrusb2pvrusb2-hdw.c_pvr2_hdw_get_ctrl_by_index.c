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
struct pvr2_hdw {unsigned int control_cnt; struct pvr2_ctrl* controls; } ;
struct pvr2_ctrl {int dummy; } ;

/* Variables and functions */

struct pvr2_ctrl *pvr2_hdw_get_ctrl_by_index(struct pvr2_hdw *hdw,
					     unsigned int idx)
{
	if (idx >= hdw->control_cnt) return NULL;
	return hdw->controls + idx;
}
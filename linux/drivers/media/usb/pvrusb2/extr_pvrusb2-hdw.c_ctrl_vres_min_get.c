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
struct pvr2_ctrl {TYPE_2__* hdw; } ;
struct TYPE_4__ {TYPE_1__* hdw_desc; } ;
struct TYPE_3__ {scalar_t__ flag_has_cx25840; } ;

/* Variables and functions */

__attribute__((used)) static int ctrl_vres_min_get(struct pvr2_ctrl *cptr,int *vp)
{
	/* Actual minimum depends on device digitizer type. */
	if (cptr->hdw->hdw_desc->flag_has_cx25840) {
		*vp = 75;
	} else {
		*vp = 17;
	}
	return 0;
}
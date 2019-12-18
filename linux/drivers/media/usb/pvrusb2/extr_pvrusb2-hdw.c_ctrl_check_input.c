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
struct pvr2_ctrl {TYPE_1__* hdw; } ;
struct TYPE_2__ {unsigned long input_allowed_mask; } ;

/* Variables and functions */
 int PVR2_CVAL_INPUT_MAX ; 

__attribute__((used)) static int ctrl_check_input(struct pvr2_ctrl *cptr,int v)
{
	if (v < 0 || v > PVR2_CVAL_INPUT_MAX)
		return 0;
	return ((1UL << v) & cptr->hdw->input_allowed_mask) != 0;
}
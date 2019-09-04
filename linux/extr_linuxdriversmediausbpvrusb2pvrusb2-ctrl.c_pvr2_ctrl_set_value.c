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
struct pvr2_ctrl {int dummy; } ;

/* Variables and functions */
 int pvr2_ctrl_set_mask_value (struct pvr2_ctrl*,int /*<<< orphan*/ ,int) ; 

int pvr2_ctrl_set_value(struct pvr2_ctrl *cptr,int val)
{
	return pvr2_ctrl_set_mask_value(cptr,~0,val);
}
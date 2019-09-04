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
struct pvr2_ctrl {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * set_value; } ;

/* Variables and functions */

int pvr2_ctrl_is_writable(struct pvr2_ctrl *cptr)
{
	if (!cptr) return 0;
	return cptr->info->set_value != NULL;
}
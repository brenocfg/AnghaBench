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
struct TYPE_2__ {int /*<<< orphan*/  sym_to_val; int /*<<< orphan*/  val_to_sym; } ;

/* Variables and functions */

int pvr2_ctrl_has_custom_symbols(struct pvr2_ctrl *cptr)
{
	if (!cptr) return 0;
	if (!cptr->info->val_to_sym) return 0;
	if (!cptr->info->sym_to_val) return 0;
	return !0;
}
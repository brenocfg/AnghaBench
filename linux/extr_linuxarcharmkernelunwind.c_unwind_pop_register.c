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
struct unwind_ctrl_block {int /*<<< orphan*/ * vrs; scalar_t__ sp_high; int /*<<< orphan*/  check_each_pop; } ;

/* Variables and functions */
 int URC_FAILURE ; 
 int URC_OK ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unwind_pop_register(struct unwind_ctrl_block *ctrl,
				unsigned long **vsp, unsigned int reg)
{
	if (unlikely(ctrl->check_each_pop))
		if (*vsp >= (unsigned long *)ctrl->sp_high)
			return -URC_FAILURE;

	ctrl->vrs[reg] = *(*vsp)++;
	return URC_OK;
}
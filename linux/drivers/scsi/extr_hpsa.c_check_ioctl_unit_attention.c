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
struct ctlr_info {int dummy; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_2__ {scalar_t__ CommandStatus; scalar_t__ ScsiStatus; } ;

/* Variables and functions */
 scalar_t__ CMD_TARGET_STATUS ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  check_for_unit_attention (struct ctlr_info*,struct CommandList*) ; 

__attribute__((used)) static void check_ioctl_unit_attention(struct ctlr_info *h,
	struct CommandList *c)
{
	if (c->err_info->CommandStatus == CMD_TARGET_STATUS &&
			c->err_info->ScsiStatus != SAM_STAT_CHECK_CONDITION)
		(void) check_for_unit_attention(h, c);
}
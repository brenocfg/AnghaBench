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
typedef  int /*<<< orphan*/  u8 ;
struct rmi_f30_ctrl_data {int address; int length; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */

__attribute__((used)) static void rmi_f30_set_ctrl_data(struct rmi_f30_ctrl_data *ctrl,
				  int *ctrl_addr, int len, u8 **reg)
{
	ctrl->address = *ctrl_addr;
	ctrl->length = len;
	ctrl->regs = *reg;
	*ctrl_addr += len;
	*reg += len;
}
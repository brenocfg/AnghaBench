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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  sem; scalar_t__ cur_rsp_mask; scalar_t__ baseaddr; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 scalar_t__ COMMS ; 
 int ETIME ; 
 scalar_t__ RESPONSE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPC_SYS_CFG ; 
 scalar_t__ SYSCFG_RDATA ; 
 int SYSCFG_START ; 
 int /*<<< orphan*/  TIMEOUT_US ; 
 scalar_t__ down_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int ve_spc_waitforcompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ve_spc_read_sys_cfg(int func, int offset, uint32_t *data)
{
	int ret;

	if (down_timeout(&info->sem, usecs_to_jiffies(TIMEOUT_US)))
		return -ETIME;

	init_completion(&info->done);
	info->cur_rsp_mask = RESPONSE_MASK(SPC_SYS_CFG);

	/* Set the control value */
	writel(SYSCFG_START | func | offset >> 2, info->baseaddr + COMMS);
	ret = ve_spc_waitforcompletion(SPC_SYS_CFG);

	if (ret == 0)
		*data = readl(info->baseaddr + SYSCFG_RDATA);

	info->cur_rsp_mask = 0;
	up(&info->sem);

	return ret;
}
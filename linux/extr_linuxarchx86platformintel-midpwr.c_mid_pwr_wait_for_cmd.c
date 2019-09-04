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
struct mid_pwr {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PM_CMD ; 
 int PM_CMD_CMD (int /*<<< orphan*/ ) ; 
 int PM_CMD_CM_IMMEDIATE ; 
 int mid_pwr_wait (struct mid_pwr*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mid_pwr_wait_for_cmd(struct mid_pwr *pwr, u8 cmd)
{
	writel(PM_CMD_CMD(cmd) | PM_CMD_CM_IMMEDIATE, pwr->regs + PM_CMD);
	return mid_pwr_wait(pwr);
}
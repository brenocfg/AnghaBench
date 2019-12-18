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
typedef  int /*<<< orphan*/  u32 ;
struct wkup_m3_ipc {scalar_t__ ipc_mem_base; } ;

/* Variables and functions */
 int AM33XX_CTRL_IPC_REG_COUNT ; 
 scalar_t__ AM33XX_CTRL_IPC_REG_OFFSET (int) ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wkup_m3_ctrl_ipc_write(struct wkup_m3_ipc *m3_ipc,
				   u32 val, int ipc_reg_num)
{
	if (WARN(ipc_reg_num < 0 || ipc_reg_num > AM33XX_CTRL_IPC_REG_COUNT,
		 "ipc register operation out of range"))
		return;

	writel(val, m3_ipc->ipc_mem_base +
	       AM33XX_CTRL_IPC_REG_OFFSET(ipc_reg_num));
}
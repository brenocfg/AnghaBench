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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ ipc_base; int /*<<< orphan*/  cmd_complete; scalar_t__ irq_mode; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ IPC_CMD ; 
 int /*<<< orphan*/  IPC_CMD_MSI ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void ipc_send_command(u32 cmd)
{
	ipcdev.cmd = cmd;
	if (ipcdev.irq_mode) {
		reinit_completion(&ipcdev.cmd_complete);
		cmd |= IPC_CMD_MSI;
	}
	writel(cmd, ipcdev.ipc_base + IPC_CMD);
}
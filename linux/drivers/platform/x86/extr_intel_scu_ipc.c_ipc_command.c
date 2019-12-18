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
typedef  int u32 ;
struct intel_scu_ipc_dev {int /*<<< orphan*/  ipc_base; int /*<<< orphan*/  cmd_complete; scalar_t__ irq_mode; } ;

/* Variables and functions */
 int IPC_IOC ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ipc_command(struct intel_scu_ipc_dev *scu, u32 cmd)
{
	if (scu->irq_mode) {
		reinit_completion(&scu->cmd_complete);
		writel(cmd | IPC_IOC, scu->ipc_base);
	}
	writel(cmd, scu->ipc_base);
}
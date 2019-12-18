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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IPCMMIS (int) ; 
 scalar_t__ IPCMxSEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_RX_MBOX ; 
 int /*<<< orphan*/  IPC_TX_MBOX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MBOX_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ipc_rcv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_base ; 
 int /*<<< orphan*/  ipc_completion ; 
 int /*<<< orphan*/  ipc_notifier ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ipc_handler(int irq, void *dev)
{
	u32 irq_stat;
	u32 data[7];

	irq_stat = readl_relaxed(ipc_base + IPCMMIS(1));
	if (irq_stat & MBOX_MASK(IPC_TX_MBOX)) {
		writel_relaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));
		complete(&ipc_completion);
	}
	if (irq_stat & MBOX_MASK(IPC_RX_MBOX)) {
		__ipc_rcv(IPC_RX_MBOX, data);
		atomic_notifier_call_chain(&ipc_notifier, data[0], data + 1);
		writel_relaxed(2, ipc_base + IPCMxSEND(IPC_RX_MBOX));
	}

	return IRQ_HANDLED;
}
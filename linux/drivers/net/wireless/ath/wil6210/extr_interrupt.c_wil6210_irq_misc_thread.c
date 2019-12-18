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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct wil6210_priv {int isr_misc; int n_msi; int suspend_resp_comp; int /*<<< orphan*/  wq; scalar_t__ suspend_resp_rcvd; int /*<<< orphan*/  platform_handle; TYPE_1__ platform_ops; int /*<<< orphan*/  recovery_state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ISR_MISC_FW_ERROR ; 
 int ISR_MISC_MBOX_EVT ; 
 int /*<<< orphan*/  WIL_PLATFORM_EVT_FW_CRASH ; 
 int /*<<< orphan*/  fw_recovery_pending ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_wil6210_irq_misc_thread (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil6210_unmask_irq_misc (struct wil6210_priv*,int) ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_fw_core_dump (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_fw_error_recovery (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_notify_fw_error (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wmi_recv_cmd (struct wil6210_priv*) ; 

__attribute__((used)) static irqreturn_t wil6210_irq_misc_thread(int irq, void *cookie)
{
	struct wil6210_priv *wil = cookie;
	u32 isr = wil->isr_misc;

	trace_wil6210_irq_misc_thread(isr);
	wil_dbg_irq(wil, "Thread ISR MISC 0x%08x\n", isr);

	if (isr & ISR_MISC_FW_ERROR) {
		wil->recovery_state = fw_recovery_pending;
		wil_fw_core_dump(wil);
		wil_notify_fw_error(wil);
		isr &= ~ISR_MISC_FW_ERROR;
		if (wil->platform_ops.notify) {
			wil_err(wil, "notify platform driver about FW crash");
			wil->platform_ops.notify(wil->platform_handle,
						 WIL_PLATFORM_EVT_FW_CRASH);
		} else {
			wil_fw_error_recovery(wil);
		}
	}
	if (isr & ISR_MISC_MBOX_EVT) {
		wil_dbg_irq(wil, "MBOX event\n");
		wmi_recv_cmd(wil);
		isr &= ~ISR_MISC_MBOX_EVT;
	}

	if (isr)
		wil_dbg_irq(wil, "un-handled MISC ISR bits 0x%08x\n", isr);

	wil->isr_misc = 0;

	wil6210_unmask_irq_misc(wil, false);

	/* in non-triple MSI case, this is done inside wil6210_thread_irq
	 * because it has to be done after unmasking the pseudo.
	 */
	if (wil->n_msi == 3 && wil->suspend_resp_rcvd) {
		wil_dbg_irq(wil, "set suspend_resp_comp to true\n");
		wil->suspend_resp_comp = true;
		wake_up_interruptible(&wil->wq);
	}

	return IRQ_HANDLED;
}
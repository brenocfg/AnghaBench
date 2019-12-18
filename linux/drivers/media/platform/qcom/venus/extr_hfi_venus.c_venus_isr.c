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
struct venus_hfi_device {int irq_status; } ;
struct venus_core {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CS_A2HSOFTINTCLR ; 
 int CPU_CS_SCIACMDARG0_INIT_IDLE_MSG_MASK ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  WRAPPER_INTR_CLEAR ; 
 int /*<<< orphan*/  WRAPPER_INTR_STATUS ; 
 int WRAPPER_INTR_STATUS_A2HWD_MASK ; 
 int WRAPPER_INTR_STATUS_A2H_MASK ; 
 struct venus_hfi_device* to_hfi_priv (struct venus_core*) ; 
 int venus_readl (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_writel (struct venus_hfi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t venus_isr(struct venus_core *core)
{
	struct venus_hfi_device *hdev = to_hfi_priv(core);
	u32 status;

	if (!hdev)
		return IRQ_NONE;

	status = venus_readl(hdev, WRAPPER_INTR_STATUS);

	if (status & WRAPPER_INTR_STATUS_A2H_MASK ||
	    status & WRAPPER_INTR_STATUS_A2HWD_MASK ||
	    status & CPU_CS_SCIACMDARG0_INIT_IDLE_MSG_MASK)
		hdev->irq_status = status;

	venus_writel(hdev, CPU_CS_A2HSOFTINTCLR, 1);
	venus_writel(hdev, WRAPPER_INTR_CLEAR, status);

	return IRQ_WAKE_THREAD;
}
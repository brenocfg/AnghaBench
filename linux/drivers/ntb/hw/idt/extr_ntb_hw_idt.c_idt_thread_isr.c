#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {TYPE_2__* pdev; } ;
struct idt_ntb_dev {TYPE_1__ ntb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IDT_NTINTSTS_DBELL ; 
 int IDT_NTINTSTS_MSG ; 
 int IDT_NTINTSTS_SEVENT ; 
 int /*<<< orphan*/  IDT_NT_NTINTSTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  idt_db_isr (struct idt_ntb_dev*,int) ; 
 int /*<<< orphan*/  idt_msg_isr (struct idt_ntb_dev*,int) ; 
 int idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_se_isr (struct idt_ntb_dev*,int) ; 

__attribute__((used)) static irqreturn_t idt_thread_isr(int irq, void *devid)
{
	struct idt_ntb_dev *ndev = devid;
	bool handled = false;
	u32 ntint_sts;

	/* Read the NT interrupts status register */
	ntint_sts = idt_nt_read(ndev, IDT_NT_NTINTSTS);

	/* Handle messaging interrupts */
	if (ntint_sts & IDT_NTINTSTS_MSG) {
		idt_msg_isr(ndev, ntint_sts);
		handled = true;
	}

	/* Handle doorbell interrupts */
	if (ntint_sts & IDT_NTINTSTS_DBELL) {
		idt_db_isr(ndev, ntint_sts);
		handled = true;
	}

	/* Handle switch event interrupts */
	if (ntint_sts & IDT_NTINTSTS_SEVENT) {
		idt_se_isr(ndev, ntint_sts);
		handled = true;
	}

	dev_dbg(&ndev->ntb.pdev->dev, "IDT IRQs 0x%08x handled", ntint_sts);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}
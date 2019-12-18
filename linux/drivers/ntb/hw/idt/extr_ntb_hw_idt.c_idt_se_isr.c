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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {TYPE_2__ ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_NTINTSTS_SEVENT ; 
 int /*<<< orphan*/  IDT_NT_NTINTSTS ; 
 int /*<<< orphan*/  IDT_SW_SEGSIGSTS ; 
 int /*<<< orphan*/  IDT_SW_SELINKDNSTS ; 
 int /*<<< orphan*/  IDT_SW_SELINKUPSTS ; 
 int /*<<< orphan*/  IDT_SW_SESTS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_sw_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_sw_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (TYPE_2__*) ; 

__attribute__((used)) static void idt_se_isr(struct idt_ntb_dev *ndev, u32 ntint_sts)
{
	u32 sests;

	/* Read Switch Events status */
	sests = idt_sw_read(ndev, IDT_SW_SESTS);

	/* Clean the Link Up/Down and Global Signal status registers */
	idt_sw_write(ndev, IDT_SW_SELINKUPSTS, (u32)-1);
	idt_sw_write(ndev, IDT_SW_SELINKDNSTS, (u32)-1);
	idt_sw_write(ndev, IDT_SW_SEGSIGSTS, (u32)-1);

	/* Clean the corresponding interrupt bit */
	idt_nt_write(ndev, IDT_NT_NTINTSTS, IDT_NTINTSTS_SEVENT);

	dev_dbg(&ndev->ntb.pdev->dev, "SE IRQ detected %#08x (SESTS %#08x)",
			  ntint_sts, sests);

	/* Notify the client driver of possible link state change */
	ntb_link_event(&ndev->ntb);
}
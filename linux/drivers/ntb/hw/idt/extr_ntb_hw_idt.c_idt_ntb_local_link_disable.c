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
struct idt_ntb_dev {int part; int /*<<< orphan*/  mtbl_lock; } ;

/* Variables and functions */
 int IDT_NTGSIGNAL_SET ; 
 int /*<<< orphan*/  IDT_NT_NTCTL ; 
 int /*<<< orphan*/  IDT_NT_NTGSIGNAL ; 
 int /*<<< orphan*/  IDT_NT_NTMTBLADDR ; 
 int /*<<< orphan*/  IDT_NT_NTMTBLDATA ; 
 int /*<<< orphan*/  IDT_SW_SEGSIGSTS ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idt_sw_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idt_ntb_local_link_disable(struct idt_ntb_dev *ndev)
{
	unsigned long irqflags;

	/* Disable Completion TLPs translation */
	idt_nt_write(ndev, IDT_NT_NTCTL, 0);

	/* Clear the corresponding NT Mapping table entry */
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_write(ndev, IDT_NT_NTMTBLADDR, ndev->part);
	idt_nt_write(ndev, IDT_NT_NTMTBLDATA, 0);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	/* Notify the peers by setting and clearing the global signal bit */
	idt_nt_write(ndev, IDT_NT_NTGSIGNAL, IDT_NTGSIGNAL_SET);
	idt_sw_write(ndev, IDT_SW_SEGSIGSTS, (u32)1 << ndev->part);
}
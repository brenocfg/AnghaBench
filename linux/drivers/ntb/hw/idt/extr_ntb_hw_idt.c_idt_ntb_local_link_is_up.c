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
struct idt_ntb_dev {int /*<<< orphan*/  mtbl_lock; int /*<<< orphan*/  part; } ;

/* Variables and functions */
 int IDT_NTCTL_CPEN ; 
 int IDT_NTMTBLDATA_VALID ; 
 int /*<<< orphan*/  IDT_NT_NTCTL ; 
 int /*<<< orphan*/  IDT_NT_NTMTBLADDR ; 
 int /*<<< orphan*/  IDT_NT_NTMTBLDATA ; 
 int /*<<< orphan*/  IDT_NT_PCICMDSTS ; 
 int IDT_PCICMDSTS_BME ; 
 int idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool idt_ntb_local_link_is_up(struct idt_ntb_dev *ndev)
{
	unsigned long irqflags;
	u32 data;

	/* Read the local Bus Master Enable status */
	data = idt_nt_read(ndev, IDT_NT_PCICMDSTS);
	if (!(data & IDT_PCICMDSTS_BME))
		return false;

	/* Read the local Completion TLPs translation enable status */
	data = idt_nt_read(ndev, IDT_NT_NTCTL);
	if (!(data & IDT_NTCTL_CPEN))
		return false;

	/* Read Mapping table entry corresponding to the local partition */
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_write(ndev, IDT_NT_NTMTBLADDR, ndev->part);
	data = idt_nt_read(ndev, IDT_NT_NTMTBLDATA);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	return !!(data & IDT_NTMTBLDATA_VALID);
}
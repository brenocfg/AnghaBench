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
typedef  int u64 ;
struct nicvf {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NICVF_INTR_MBOX_MASK ; 
 int /*<<< orphan*/  NIC_VF_INT ; 
 int /*<<< orphan*/  nicvf_dump_intr_status (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_handle_mbx_intr (struct nicvf*) ; 
 int nicvf_reg_read (struct nicvf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t nicvf_misc_intr_handler(int irq, void *nicvf_irq)
{
	struct nicvf *nic = (struct nicvf *)nicvf_irq;
	u64 intr;

	nicvf_dump_intr_status(nic);

	intr = nicvf_reg_read(nic, NIC_VF_INT);
	/* Check for spurious interrupt */
	if (!(intr & NICVF_INTR_MBOX_MASK))
		return IRQ_HANDLED;

	nicvf_handle_mbx_intr(nic);

	return IRQ_HANDLED;
}
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
struct mxic_nand_ctlr {int /*<<< orphan*/  complete; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INT_RDY_PIN ; 
 scalar_t__ INT_STS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxic_nfc_isr(int irq, void *dev_id)
{
	struct mxic_nand_ctlr *nfc = dev_id;
	u32 sts;

	sts = readl(nfc->regs + INT_STS);
	if (sts & INT_RDY_PIN)
		complete(&nfc->complete);
	else
		return IRQ_NONE;

	return IRQ_HANDLED;
}
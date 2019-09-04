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
struct atmel_isi {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISI_CTRL_DIS ; 
 int ISI_CTRL_SRST ; 
 int /*<<< orphan*/  ISI_INTDIS ; 
 int /*<<< orphan*/  ISI_INTMASK ; 
 int ISI_SR_CXFR_DONE ; 
 int ISI_SR_PXFR_DONE ; 
 int /*<<< orphan*/  ISI_STATUS ; 
 int /*<<< orphan*/  atmel_isi_handle_streaming (struct atmel_isi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int isi_readl (struct atmel_isi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isi_writel (struct atmel_isi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t isi_interrupt(int irq, void *dev_id)
{
	struct atmel_isi *isi = dev_id;
	u32 status, mask, pending;
	irqreturn_t ret = IRQ_NONE;

	spin_lock(&isi->irqlock);

	status = isi_readl(isi, ISI_STATUS);
	mask = isi_readl(isi, ISI_INTMASK);
	pending = status & mask;

	if (pending & ISI_CTRL_SRST) {
		complete(&isi->complete);
		isi_writel(isi, ISI_INTDIS, ISI_CTRL_SRST);
		ret = IRQ_HANDLED;
	} else if (pending & ISI_CTRL_DIS) {
		complete(&isi->complete);
		isi_writel(isi, ISI_INTDIS, ISI_CTRL_DIS);
		ret = IRQ_HANDLED;
	} else {
		if (likely(pending & ISI_SR_CXFR_DONE) ||
				likely(pending & ISI_SR_PXFR_DONE))
			ret = atmel_isi_handle_streaming(isi);
	}

	spin_unlock(&isi->irqlock);
	return ret;
}
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
struct TYPE_2__ {int /*<<< orphan*/ * hba_eq_hdl; } ;
struct lpfc_hba {int cfg_irq_chann; TYPE_1__ sli4_hba; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ lpfc_sli4_hba_intr_handler (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t
lpfc_sli4_intr_handler(int irq, void *dev_id)
{
	struct lpfc_hba  *phba;
	irqreturn_t hba_irq_rc;
	bool hba_handled = false;
	int qidx;

	/* Get the driver's phba structure from the dev_id */
	phba = (struct lpfc_hba *)dev_id;

	if (unlikely(!phba))
		return IRQ_NONE;

	/*
	 * Invoke fast-path host attention interrupt handling as appropriate.
	 */
	for (qidx = 0; qidx < phba->cfg_irq_chann; qidx++) {
		hba_irq_rc = lpfc_sli4_hba_intr_handler(irq,
					&phba->sli4_hba.hba_eq_hdl[qidx]);
		if (hba_irq_rc == IRQ_HANDLED)
			hba_handled |= true;
	}

	return (hba_handled == true) ? IRQ_HANDLED : IRQ_NONE;
}
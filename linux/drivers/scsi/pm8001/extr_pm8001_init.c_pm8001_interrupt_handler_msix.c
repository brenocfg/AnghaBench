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
struct pm8001_hba_info {int /*<<< orphan*/ * tasklet; } ;
struct isr_param {size_t irq_id; struct pm8001_hba_info* drv_inst; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* isr ) (struct pm8001_hba_info*,size_t) ;int /*<<< orphan*/  (* is_our_interrupt ) (struct pm8001_hba_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_1__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  stub2 (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t pm8001_interrupt_handler_msix(int irq, void *opaque)
{
	struct isr_param *irq_vector;
	struct pm8001_hba_info *pm8001_ha;
	irqreturn_t ret = IRQ_HANDLED;
	irq_vector = (struct isr_param *)opaque;
	pm8001_ha = irq_vector->drv_inst;

	if (unlikely(!pm8001_ha))
		return IRQ_NONE;
	if (!PM8001_CHIP_DISP->is_our_interrupt(pm8001_ha))
		return IRQ_NONE;
#ifdef PM8001_USE_TASKLET
	tasklet_schedule(&pm8001_ha->tasklet[irq_vector->irq_id]);
#else
	ret = PM8001_CHIP_DISP->isr(pm8001_ha, irq_vector->irq_id);
#endif
	return ret;
}
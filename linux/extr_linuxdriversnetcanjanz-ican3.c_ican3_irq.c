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
typedef  int u8 ;
struct ican3_dev {int num; int /*<<< orphan*/  napi; TYPE_2__* ctrl; TYPE_1__* dpmctrl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  int_disable; } ;
struct TYPE_3__ {int /*<<< orphan*/  interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ican3_irq(int irq, void *dev_id)
{
	struct ican3_dev *mod = dev_id;
	u8 stat;

	/*
	 * The interrupt status register on this device reports interrupts
	 * as zeroes instead of using ones like most other devices
	 */
	stat = ioread8(&mod->ctrl->int_disable) & (1 << mod->num);
	if (stat == (1 << mod->num))
		return IRQ_NONE;

	/* clear the MODULbus interrupt from the microcontroller */
	ioread8(&mod->dpmctrl->interrupt);

	/* disable interrupt generation, schedule the NAPI poller */
	iowrite8(1 << mod->num, &mod->ctrl->int_disable);
	napi_schedule(&mod->napi);
	return IRQ_HANDLED;
}
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
struct brcmnand_controller {TYPE_1__* soc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ (* ctlrdy_ack ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  brcmnand_ctlrdy_irq (int,void*) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t brcmnand_irq(int irq, void *data)
{
	struct brcmnand_controller *ctrl = data;

	if (ctrl->soc->ctlrdy_ack(ctrl->soc))
		return brcmnand_ctlrdy_irq(irq, data);

	return IRQ_NONE;
}
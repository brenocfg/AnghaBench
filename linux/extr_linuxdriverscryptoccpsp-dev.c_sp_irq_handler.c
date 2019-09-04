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
struct sp_device {int /*<<< orphan*/  psp_irq_data; int /*<<< orphan*/  (* psp_irq_handler ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ccp_irq_data; int /*<<< orphan*/  (* ccp_irq_handler ) (int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sp_irq_handler(int irq, void *data)
{
	struct sp_device *sp = data;

	if (sp->ccp_irq_handler)
		sp->ccp_irq_handler(irq, sp->ccp_irq_data);

	if (sp->psp_irq_handler)
		sp->psp_irq_handler(irq, sp->psp_irq_data);

	return IRQ_HANDLED;
}
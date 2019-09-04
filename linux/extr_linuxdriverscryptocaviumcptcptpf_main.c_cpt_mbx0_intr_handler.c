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
struct cpt_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cpt_mbox_intr_handler (struct cpt_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cpt_mbx0_intr_handler(int irq, void *cpt_irq)
{
	struct cpt_device *cpt = (struct cpt_device *)cpt_irq;

	cpt_mbox_intr_handler(cpt, 0);

	return IRQ_HANDLED;
}
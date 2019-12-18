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
struct pcifront_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_pcifront_aer_op (struct pcifront_device*) ; 

__attribute__((used)) static irqreturn_t pcifront_handler_aer(int irq, void *dev)
{
	struct pcifront_device *pdev = dev;
	schedule_pcifront_aer_op(pdev);
	return IRQ_HANDLED;
}
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
struct intel_scu_ipc_dev {int /*<<< orphan*/  cmd_complete; scalar_t__ irq_mode; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ioc(int irq, void *dev_id)
{
	struct intel_scu_ipc_dev *scu = dev_id;

	if (scu->irq_mode)
		complete(&scu->cmd_complete);

	return IRQ_HANDLED;
}
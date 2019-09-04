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
typedef  int /*<<< orphan*/  u32 ;
struct smi_rc {int dummy; } ;
struct smi_port {int dummy; } ;
struct smi_dev {TYPE_1__* info; struct smi_rc ir; struct smi_port* ts_port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ ts_1; scalar_t__ ts_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  MSI_INT_STATUS ; 
 scalar_t__ smi_ir_irq (struct smi_rc*,int /*<<< orphan*/ ) ; 
 scalar_t__ smi_port_irq (struct smi_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t smi_irq_handler(int irq, void *dev_id)
{
	struct smi_dev *dev = dev_id;
	struct smi_port *port0 = &dev->ts_port[0];
	struct smi_port *port1 = &dev->ts_port[1];
	struct smi_rc *ir = &dev->ir;
	int handled = 0;

	u32 intr_status = smi_read(MSI_INT_STATUS);

	/* ts0 interrupt.*/
	if (dev->info->ts_0)
		handled += smi_port_irq(port0, intr_status);

	/* ts1 interrupt.*/
	if (dev->info->ts_1)
		handled += smi_port_irq(port1, intr_status);

	/* ir interrupt.*/
	handled += smi_ir_irq(ir, intr_status);

	return IRQ_RETVAL(handled);
}
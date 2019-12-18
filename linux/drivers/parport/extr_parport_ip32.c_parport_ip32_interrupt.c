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
struct parport_ip32_private {int irq_mode; } ;
struct parport {TYPE_1__* physport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum parport_ip32_irq_mode { ____Placeholder_parport_ip32_irq_mode } parport_ip32_irq_mode ;
struct TYPE_2__ {struct parport_ip32_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  PARPORT_IP32_IRQ_FWD 129 
#define  PARPORT_IP32_IRQ_HERE 128 
 int /*<<< orphan*/  parport_ip32_wakeup (struct parport* const) ; 
 int /*<<< orphan*/  parport_irq_handler (int,void*) ; 

__attribute__((used)) static irqreturn_t parport_ip32_interrupt(int irq, void *dev_id)
{
	struct parport * const p = dev_id;
	struct parport_ip32_private * const priv = p->physport->private_data;
	enum parport_ip32_irq_mode irq_mode = priv->irq_mode;

	switch (irq_mode) {
	case PARPORT_IP32_IRQ_FWD:
		return parport_irq_handler(irq, dev_id);

	case PARPORT_IP32_IRQ_HERE:
		parport_ip32_wakeup(p);
		break;
	}

	return IRQ_HANDLED;
}
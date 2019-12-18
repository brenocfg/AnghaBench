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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ibm_iic_private {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ iic_force_poll ; 
 int /*<<< orphan*/  iic_handler ; 
 int /*<<< orphan*/  iic_interrupt_mode (struct ibm_iic_private*,int /*<<< orphan*/ ) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ibm_iic_private*) ; 

__attribute__((used)) static int iic_request_irq(struct platform_device *ofdev,
				     struct ibm_iic_private *dev)
{
	struct device_node *np = ofdev->dev.of_node;
	int irq;

	if (iic_force_poll)
		return 0;

	irq = irq_of_parse_and_map(np, 0);
	if (!irq) {
		dev_err(&ofdev->dev, "irq_of_parse_and_map failed\n");
		return 0;
	}

	/* Disable interrupts until we finish initialization, assumes
	 *  level-sensitive IRQ setup...
	 */
	iic_interrupt_mode(dev, 0);
	if (request_irq(irq, iic_handler, 0, "IBM IIC", dev)) {
		dev_err(&ofdev->dev, "request_irq %d failed\n", irq);
		/* Fallback to the polling mode */
		return 0;
	}

	return irq;
}
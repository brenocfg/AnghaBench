#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {unsigned int phyirq; struct irq_domain* irqdomain; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/ * irqchip; int /*<<< orphan*/  irqenable; int /*<<< orphan*/  irq_lock; } ;
struct lan78xx_net {TYPE_4__ domain_data; TYPE_3__* udev; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_1__* parent; } ;
struct TYPE_7__ {TYPE_2__ dev; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INT_EP_CTL ; 
 int /*<<< orphan*/  INT_EP_PHY ; 
 int /*<<< orphan*/  MAX_INT_EP ; 
 int /*<<< orphan*/  chip_domain_ops ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 unsigned int irq_create_mapping (struct irq_domain*,int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_domain_add_simple (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  irq_domain_remove (struct irq_domain*) ; 
 int /*<<< orphan*/  lan78xx_irqchip ; 
 int /*<<< orphan*/  lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan78xx_setup_irq_domain(struct lan78xx_net *dev)
{
	struct device_node *of_node;
	struct irq_domain *irqdomain;
	unsigned int irqmap = 0;
	u32 buf;
	int ret = 0;

	of_node = dev->udev->dev.parent->of_node;

	mutex_init(&dev->domain_data.irq_lock);

	lan78xx_read_reg(dev, INT_EP_CTL, &buf);
	dev->domain_data.irqenable = buf;

	dev->domain_data.irqchip = &lan78xx_irqchip;
	dev->domain_data.irq_handler = handle_simple_irq;

	irqdomain = irq_domain_add_simple(of_node, MAX_INT_EP, 0,
					  &chip_domain_ops, &dev->domain_data);
	if (irqdomain) {
		/* create mapping for PHY interrupt */
		irqmap = irq_create_mapping(irqdomain, INT_EP_PHY);
		if (!irqmap) {
			irq_domain_remove(irqdomain);

			irqdomain = NULL;
			ret = -EINVAL;
		}
	} else {
		ret = -EINVAL;
	}

	dev->domain_data.irqdomain = irqdomain;
	dev->domain_data.phyirq = irqmap;

	return ret;
}
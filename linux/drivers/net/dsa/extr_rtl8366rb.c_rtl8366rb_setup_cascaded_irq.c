#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct realtek_smi {int num_ports; int /*<<< orphan*/  irqdomain; TYPE_1__* dev; int /*<<< orphan*/  map; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
#define  IRQF_TRIGGER_FALLING 131 
#define  IRQF_TRIGGER_HIGH 130 
#define  IRQF_TRIGGER_LOW 129 
#define  IRQF_TRIGGER_RISING 128 
 int /*<<< orphan*/  RTL8366RB_INTERRUPT_CONTROL_REG ; 
 int /*<<< orphan*/  RTL8366RB_INTERRUPT_POLARITY ; 
 int /*<<< orphan*/  RTL8366RB_INTERRUPT_STATUS_REG ; 
 int /*<<< orphan*/  RTL8366RB_NUM_INTERRUPT ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct realtek_smi*) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct realtek_smi*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int /*<<< orphan*/  irq_set_parent (int /*<<< orphan*/ ,int) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8366rb_irq ; 
 int /*<<< orphan*/  rtl8366rb_irqdomain_ops ; 

__attribute__((used)) static int rtl8366rb_setup_cascaded_irq(struct realtek_smi *smi)
{
	struct device_node *intc;
	unsigned long irq_trig;
	int irq;
	int ret;
	u32 val;
	int i;

	intc = of_get_child_by_name(smi->dev->of_node, "interrupt-controller");
	if (!intc) {
		dev_err(smi->dev, "missing child interrupt-controller node\n");
		return -EINVAL;
	}
	/* RB8366RB IRQs cascade off this one */
	irq = of_irq_get(intc, 0);
	if (irq <= 0) {
		dev_err(smi->dev, "failed to get parent IRQ\n");
		ret = irq ? irq : -EINVAL;
		goto out_put_node;
	}

	/* This clears the IRQ status register */
	ret = regmap_read(smi->map, RTL8366RB_INTERRUPT_STATUS_REG,
			  &val);
	if (ret) {
		dev_err(smi->dev, "can't read interrupt status\n");
		goto out_put_node;
	}

	/* Fetch IRQ edge information from the descriptor */
	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	switch (irq_trig) {
	case IRQF_TRIGGER_RISING:
	case IRQF_TRIGGER_HIGH:
		dev_info(smi->dev, "active high/rising IRQ\n");
		val = 0;
		break;
	case IRQF_TRIGGER_FALLING:
	case IRQF_TRIGGER_LOW:
		dev_info(smi->dev, "active low/falling IRQ\n");
		val = RTL8366RB_INTERRUPT_POLARITY;
		break;
	}
	ret = regmap_update_bits(smi->map, RTL8366RB_INTERRUPT_CONTROL_REG,
				 RTL8366RB_INTERRUPT_POLARITY,
				 val);
	if (ret) {
		dev_err(smi->dev, "could not configure IRQ polarity\n");
		goto out_put_node;
	}

	ret = devm_request_threaded_irq(smi->dev, irq, NULL,
					rtl8366rb_irq, IRQF_ONESHOT,
					"RTL8366RB", smi);
	if (ret) {
		dev_err(smi->dev, "unable to request irq: %d\n", ret);
		goto out_put_node;
	}
	smi->irqdomain = irq_domain_add_linear(intc,
					       RTL8366RB_NUM_INTERRUPT,
					       &rtl8366rb_irqdomain_ops,
					       smi);
	if (!smi->irqdomain) {
		dev_err(smi->dev, "failed to create IRQ domain\n");
		ret = -EINVAL;
		goto out_put_node;
	}
	for (i = 0; i < smi->num_ports; i++)
		irq_set_parent(irq_create_mapping(smi->irqdomain, i), irq);

out_put_node:
	of_node_put(intc);
	return ret;
}
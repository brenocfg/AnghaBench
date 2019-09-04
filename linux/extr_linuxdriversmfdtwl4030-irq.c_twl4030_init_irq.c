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
struct irq_chip {char* name; int /*<<< orphan*/  irq_ack; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int TWL4030_CORE_NR_IRQS ; 
 int /*<<< orphan*/  TWL4030_MODULE_INT ; 
 int TWL4030_PWR_NR_IRQS ; 
 int /*<<< orphan*/  activate_irq (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,int,int,int) ; 
 struct irq_chip dummy_irq_chip ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 int /*<<< orphan*/ * handle_simple_irq ; 
 int /*<<< orphan*/  handle_twl4030_pih ; 
 int irq_alloc_descs (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_legacy (struct device_node*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_simple_ops ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,struct irq_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_nested_thread (int,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int twl4030_init_sih_modules (int /*<<< orphan*/ ) ; 
 int twl4030_irq_base ; 
 TYPE_1__ twl4030_sih_irq_chip ; 
 int twl4030_sih_setup (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  twl_irq_line ; 

int twl4030_init_irq(struct device *dev, int irq_num)
{
	static struct irq_chip	twl4030_irq_chip;
	int			status, i;
	int			irq_base, irq_end, nr_irqs;
	struct			device_node *node = dev->of_node;

	/*
	 * TWL core and pwr interrupts must be contiguous because
	 * the hwirqs numbers are defined contiguously from 1 to 15.
	 * Create only one domain for both.
	 */
	nr_irqs = TWL4030_PWR_NR_IRQS + TWL4030_CORE_NR_IRQS;

	irq_base = irq_alloc_descs(-1, 0, nr_irqs, 0);
	if (irq_base < 0) {
		dev_err(dev, "Fail to allocate IRQ descs\n");
		return irq_base;
	}

	irq_domain_add_legacy(node, nr_irqs, irq_base, 0,
			      &irq_domain_simple_ops, NULL);

	irq_end = irq_base + TWL4030_CORE_NR_IRQS;

	/*
	 * Mask and clear all TWL4030 interrupts since initially we do
	 * not have any TWL4030 module interrupt handlers present
	 */
	status = twl4030_init_sih_modules(twl_irq_line);
	if (status < 0)
		return status;

	twl4030_irq_base = irq_base;

	/*
	 * Install an irq handler for each of the SIH modules;
	 * clone dummy irq_chip since PIH can't *do* anything
	 */
	twl4030_irq_chip = dummy_irq_chip;
	twl4030_irq_chip.name = "twl4030";

	twl4030_sih_irq_chip.irq_ack = dummy_irq_chip.irq_ack;

	for (i = irq_base; i < irq_end; i++) {
		irq_set_chip_and_handler(i, &twl4030_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thread(i, 1);
		activate_irq(i);
	}

	dev_info(dev, "%s (irq %d) chaining IRQs %d..%d\n", "PIH",
			irq_num, irq_base, irq_end);

	/* ... and the PWR_INT module ... */
	status = twl4030_sih_setup(dev, TWL4030_MODULE_INT, irq_end);
	if (status < 0) {
		dev_err(dev, "sih_setup PWR INT --> %d\n", status);
		goto fail;
	}

	/* install an irq handler to demultiplex the TWL4030 interrupt */
	status = request_threaded_irq(irq_num, NULL, handle_twl4030_pih,
				      IRQF_ONESHOT,
				      "TWL4030-PIH", NULL);
	if (status < 0) {
		dev_err(dev, "could not claim irq%d: %d\n", irq_num, status);
		goto fail_rqirq;
	}
	enable_irq_wake(irq_num);

	return irq_base;
fail_rqirq:
	/* clean up twl4030_sih_setup */
fail:
	for (i = irq_base; i < irq_end; i++) {
		irq_set_nested_thread(i, 0);
		irq_set_chip_and_handler(i, NULL, NULL);
	}

	return status;
}
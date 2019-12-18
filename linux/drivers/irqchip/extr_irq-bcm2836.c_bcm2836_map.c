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
struct irq_domain {int /*<<< orphan*/  host_data; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
#define  LOCAL_IRQ_CNTHPIRQ 133 
#define  LOCAL_IRQ_CNTPNSIRQ 132 
#define  LOCAL_IRQ_CNTPSIRQ 131 
#define  LOCAL_IRQ_CNTVIRQ 130 
#define  LOCAL_IRQ_GPU_FAST 129 
#define  LOCAL_IRQ_PMU_FAST 128 
 struct irq_chip bcm2836_arm_irqchip_gpu ; 
 struct irq_chip bcm2836_arm_irqchip_pmu ; 
 struct irq_chip bcm2836_arm_irqchip_timer ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2836_map(struct irq_domain *d, unsigned int irq,
		       irq_hw_number_t hw)
{
	struct irq_chip *chip;

	switch (hw) {
	case LOCAL_IRQ_CNTPSIRQ:
	case LOCAL_IRQ_CNTPNSIRQ:
	case LOCAL_IRQ_CNTHPIRQ:
	case LOCAL_IRQ_CNTVIRQ:
		chip = &bcm2836_arm_irqchip_timer;
		break;
	case LOCAL_IRQ_GPU_FAST:
		chip = &bcm2836_arm_irqchip_gpu;
		break;
	case LOCAL_IRQ_PMU_FAST:
		chip = &bcm2836_arm_irqchip_pmu;
		break;
	default:
		pr_warn_once("Unexpected hw irq: %lu\n", hw);
		return -EINVAL;
	}

	irq_set_percpu_devid(irq);
	irq_domain_set_info(d, irq, hw, chip, d->host_data,
			    handle_percpu_devid_irq, NULL, NULL);
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

	return 0;
}
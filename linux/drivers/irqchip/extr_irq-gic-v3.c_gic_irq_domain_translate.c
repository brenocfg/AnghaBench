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
struct irq_fwspec {int param_count; int* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EPPI_BASE_INTID ; 
 int /*<<< orphan*/  ESPI_BASE_INTID ; 
#define  GIC_IRQ_TYPE_LPI 129 
#define  GIC_IRQ_TYPE_PARTITION 128 
 unsigned int IRQ_TYPE_NONE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_fwnode_irqchip (int /*<<< orphan*/ ) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gic_irq_domain_translate(struct irq_domain *d,
				    struct irq_fwspec *fwspec,
				    unsigned long *hwirq,
				    unsigned int *type)
{
	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->param_count < 3)
			return -EINVAL;

		switch (fwspec->param[0]) {
		case 0:			/* SPI */
			*hwirq = fwspec->param[1] + 32;
			break;
		case 1:			/* PPI */
			*hwirq = fwspec->param[1] + 16;
			break;
		case 2:			/* ESPI */
			*hwirq = fwspec->param[1] + ESPI_BASE_INTID;
			break;
		case 3:			/* EPPI */
			*hwirq = fwspec->param[1] + EPPI_BASE_INTID;
			break;
		case GIC_IRQ_TYPE_LPI:	/* LPI */
			*hwirq = fwspec->param[1];
			break;
		case GIC_IRQ_TYPE_PARTITION:
			*hwirq = fwspec->param[1];
			if (fwspec->param[1] >= 16)
				*hwirq += EPPI_BASE_INTID - 16;
			else
				*hwirq += 16;
			break;
		default:
			return -EINVAL;
		}

		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

		/*
		 * Make it clear that broken DTs are... broken.
		 * Partitionned PPIs are an unfortunate exception.
		 */
		WARN_ON(*type == IRQ_TYPE_NONE &&
			fwspec->param[0] != GIC_IRQ_TYPE_PARTITION);
		return 0;
	}

	if (is_fwnode_irqchip(fwspec->fwnode)) {
		if(fwspec->param_count != 2)
			return -EINVAL;

		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];

		WARN_ON(*type == IRQ_TYPE_NONE);
		return 0;
	}

	return -EINVAL;
}
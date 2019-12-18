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
typedef  int u32 ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct dpu_mdss {TYPE_1__ irq_controller; scalar_t__ mmio; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 scalar_t__ HW_INTR_STATUS ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int fls (int) ; 
 int generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct dpu_mdss* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void dpu_mdss_irq(struct irq_desc *desc)
{
	struct dpu_mdss *dpu_mdss = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	u32 interrupts;

	chained_irq_enter(chip, desc);

	interrupts = readl_relaxed(dpu_mdss->mmio + HW_INTR_STATUS);

	while (interrupts) {
		irq_hw_number_t hwirq = fls(interrupts) - 1;
		unsigned int mapping;
		int rc;

		mapping = irq_find_mapping(dpu_mdss->irq_controller.domain,
					   hwirq);
		if (mapping == 0) {
			DRM_ERROR("couldn't find irq mapping for %lu\n", hwirq);
			break;
		}

		rc = generic_handle_irq(mapping);
		if (rc < 0) {
			DRM_ERROR("handle irq fail: irq=%lu mapping=%u rc=%d\n",
				  hwirq, mapping, rc);
			break;
		}

		interrupts &= ~(1 << hwirq);
	}

	chained_irq_exit(chip, desc);
}
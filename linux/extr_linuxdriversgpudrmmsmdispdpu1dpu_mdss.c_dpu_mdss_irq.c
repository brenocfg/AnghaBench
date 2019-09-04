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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct dpu_mdss {TYPE_1__ irq_controller; scalar_t__ mmio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 scalar_t__ HW_INTR_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int fls (int) ; 
 int generic_handle_irq (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static irqreturn_t dpu_mdss_irq(int irq, void *arg)
{
	struct dpu_mdss *dpu_mdss = arg;
	u32 interrupts;

	interrupts = readl_relaxed(dpu_mdss->mmio + HW_INTR_STATUS);

	while (interrupts) {
		irq_hw_number_t hwirq = fls(interrupts) - 1;
		unsigned int mapping;
		int rc;

		mapping = irq_find_mapping(dpu_mdss->irq_controller.domain,
					   hwirq);
		if (mapping == 0) {
			DRM_ERROR("couldn't find irq mapping for %lu\n", hwirq);
			return IRQ_NONE;
		}

		rc = generic_handle_irq(mapping);
		if (rc < 0) {
			DRM_ERROR("handle irq fail: irq=%lu mapping=%u rc=%d\n",
				  hwirq, mapping, rc);
			return IRQ_NONE;
		}

		interrupts &= ~(1 << hwirq);
	}

	return IRQ_HANDLED;
}
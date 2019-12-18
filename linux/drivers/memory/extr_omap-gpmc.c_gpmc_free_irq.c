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
struct gpmc_device {int nirqs; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gpmc_device*) ; 
 int /*<<< orphan*/ * gpmc_irq_domain ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gpmc_free_irq(struct gpmc_device *gpmc)
{
	int hwirq;

	free_irq(gpmc->irq, gpmc);

	for (hwirq = 0; hwirq < gpmc->nirqs; hwirq++)
		irq_dispose_mapping(irq_find_mapping(gpmc_irq_domain, hwirq));

	irq_domain_remove(gpmc_irq_domain);
	gpmc_irq_domain = NULL;

	return 0;
}
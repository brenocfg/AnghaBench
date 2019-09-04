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
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int NUM_PRCMU_WAKEUPS ; 
 int /*<<< orphan*/  db8500_irq_domain ; 
 int /*<<< orphan*/  db8500_irq_ops ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_simple (struct device_node*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int db8500_irq_init(struct device_node *np)
{
	int i;

	db8500_irq_domain = irq_domain_add_simple(
		np, NUM_PRCMU_WAKEUPS, 0,
		&db8500_irq_ops, NULL);

	if (!db8500_irq_domain) {
		pr_err("Failed to create irqdomain\n");
		return -ENOSYS;
	}

	/* All wakeups will be used, so create mappings for all */
	for (i = 0; i < NUM_PRCMU_WAKEUPS; i++)
		irq_create_mapping(db8500_irq_domain, i);

	return 0;
}
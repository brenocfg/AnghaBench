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
struct device_node {int dummy; } ;
struct ab8500 {TYPE_1__* dev; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int AB8500_NR_IRQS ; 
 int AB8505_NR_IRQS ; 
 int AB8540_NR_IRQS ; 
 int AB9540_NR_IRQS ; 
 int ENODEV ; 
 int /*<<< orphan*/  ab8500_irq_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ab8500*) ; 
 scalar_t__ is_ab8505 (struct ab8500*) ; 
 scalar_t__ is_ab8540 (struct ab8500*) ; 
 scalar_t__ is_ab9540 (struct ab8500*) ; 

__attribute__((used)) static int ab8500_irq_init(struct ab8500 *ab8500, struct device_node *np)
{
	int num_irqs;

	if (is_ab8540(ab8500))
		num_irqs = AB8540_NR_IRQS;
	else if (is_ab9540(ab8500))
		num_irqs = AB9540_NR_IRQS;
	else if (is_ab8505(ab8500))
		num_irqs = AB8505_NR_IRQS;
	else
		num_irqs = AB8500_NR_IRQS;

	/* If ->irq_base is zero this will give a linear mapping */
	ab8500->domain = irq_domain_add_simple(ab8500->dev->of_node,
					       num_irqs, 0,
					       &ab8500_irq_ops, ab8500);

	if (!ab8500->domain) {
		dev_err(ab8500->dev, "Failed to create irqdomain\n");
		return -ENODEV;
	}

	return 0;
}
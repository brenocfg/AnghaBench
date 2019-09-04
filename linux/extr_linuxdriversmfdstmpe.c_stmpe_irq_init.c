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
struct stmpe {int /*<<< orphan*/  dev; int /*<<< orphan*/  domain; TYPE_1__* variant; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int num_irqs; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_domain_add_simple (struct device_node*,int,int,int /*<<< orphan*/ *,struct stmpe*) ; 
 int /*<<< orphan*/  stmpe_irq_ops ; 

__attribute__((used)) static int stmpe_irq_init(struct stmpe *stmpe, struct device_node *np)
{
	int base = 0;
	int num_irqs = stmpe->variant->num_irqs;

	stmpe->domain = irq_domain_add_simple(np, num_irqs, base,
					      &stmpe_irq_ops, stmpe);
	if (!stmpe->domain) {
		dev_err(stmpe->dev, "Failed to create irqdomain\n");
		return -ENOSYS;
	}

	return 0;
}
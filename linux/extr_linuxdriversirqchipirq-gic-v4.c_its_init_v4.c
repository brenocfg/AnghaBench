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
struct irq_domain_ops {int dummy; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct irq_domain* gic_domain ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct irq_domain_ops const* vpe_domain_ops ; 

int its_init_v4(struct irq_domain *domain, const struct irq_domain_ops *ops)
{
	if (domain) {
		pr_info("ITS: Enabling GICv4 support\n");
		gic_domain = domain;
		vpe_domain_ops = ops;
		return 0;
	}

	pr_err("ITS: No GICv4 VPE domain allocated\n");
	return -ENODEV;
}
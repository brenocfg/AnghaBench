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
typedef  int /*<<< orphan*/  u32 ;
struct of_phandle_args {scalar_t__ np; int args_count; int /*<<< orphan*/ * args; } ;
struct irq_domain {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ irq_domain_get_of_node (struct irq_domain*) ; 
 int of_parse_phandle_with_args (int /*<<< orphan*/ ,char*,char*,int,struct of_phandle_args*) ; 

__attribute__((used)) static int of_pmsi_get_dev_id(struct irq_domain *domain, struct device *dev,
				  u32 *dev_id)
{
	int ret, index = 0;

	/* Suck the DeviceID out of the msi-parent property */
	do {
		struct of_phandle_args args;

		ret = of_parse_phandle_with_args(dev->of_node,
						 "msi-parent", "#msi-cells",
						 index, &args);
		if (args.np == irq_domain_get_of_node(domain)) {
			if (WARN_ON(args.args_count != 1))
				return -EINVAL;
			*dev_id = args.args[0];
			break;
		}
		index++;
	} while (!ret);

	return ret;
}
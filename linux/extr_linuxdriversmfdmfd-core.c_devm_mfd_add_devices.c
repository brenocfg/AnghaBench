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
struct resource {int dummy; } ;
struct mfd_cell {int dummy; } ;
struct irq_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_mfd_dev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct device**) ; 
 struct device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct device**) ; 
 int mfd_add_devices (struct device*,int,struct mfd_cell const*,int,struct resource*,int,struct irq_domain*) ; 

int devm_mfd_add_devices(struct device *dev, int id,
			 const struct mfd_cell *cells, int n_devs,
			 struct resource *mem_base,
			 int irq_base, struct irq_domain *domain)
{
	struct device **ptr;
	int ret;

	ptr = devres_alloc(devm_mfd_dev_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = mfd_add_devices(dev, id, cells, n_devs, mem_base,
			      irq_base, domain);
	if (ret < 0) {
		devres_free(ptr);
		return ret;
	}

	*ptr = dev;
	devres_add(dev, ptr);

	return ret;
}
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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_pci_unmap_iospace ; 
 int /*<<< orphan*/  devres_add (struct device*,struct resource const**) ; 
 struct resource** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct resource const**) ; 
 int pci_remap_iospace (struct resource const*,int /*<<< orphan*/ ) ; 

int devm_pci_remap_iospace(struct device *dev, const struct resource *res,
			   phys_addr_t phys_addr)
{
	const struct resource **ptr;
	int error;

	ptr = devres_alloc(devm_pci_unmap_iospace, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	error = pci_remap_iospace(res, phys_addr);
	if (error) {
		devres_free(ptr);
	} else	{
		*ptr = res;
		devres_add(dev, ptr);
	}

	return error;
}
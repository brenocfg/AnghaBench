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
struct pci_epc_ops {int dummy; } ;
struct pci_epc {int dummy; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pci_epc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct pci_epc*) ; 
 struct pci_epc* __pci_epc_create (struct device*,struct pci_epc_ops const*,struct module*) ; 
 int /*<<< orphan*/  devm_pci_epc_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct pci_epc**) ; 
 struct pci_epc** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct pci_epc**) ; 

struct pci_epc *
__devm_pci_epc_create(struct device *dev, const struct pci_epc_ops *ops,
		      struct module *owner)
{
	struct pci_epc **ptr, *epc;

	ptr = devres_alloc(devm_pci_epc_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	epc = __pci_epc_create(dev, ops, owner);
	if (!IS_ERR(epc)) {
		*ptr = epc;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return epc;
}
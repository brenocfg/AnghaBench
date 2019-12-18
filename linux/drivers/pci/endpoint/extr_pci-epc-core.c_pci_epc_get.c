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
struct pci_epc {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct device {int dummy; } ;
struct class_dev_iter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pci_epc* ERR_PTR (int) ; 
 int /*<<< orphan*/  class_dev_iter_exit (struct class_dev_iter*) ; 
 int /*<<< orphan*/  class_dev_iter_init (struct class_dev_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* class_dev_iter_next (struct class_dev_iter*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_epc_class ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct pci_epc* to_pci_epc (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct pci_epc *pci_epc_get(const char *epc_name)
{
	int ret = -EINVAL;
	struct pci_epc *epc;
	struct device *dev;
	struct class_dev_iter iter;

	class_dev_iter_init(&iter, pci_epc_class, NULL, NULL);
	while ((dev = class_dev_iter_next(&iter))) {
		if (strcmp(epc_name, dev_name(dev)))
			continue;

		epc = to_pci_epc(dev);
		if (!try_module_get(epc->ops->owner)) {
			ret = -EINVAL;
			goto err;
		}

		class_dev_iter_exit(&iter);
		get_device(&epc->dev);
		return epc;
	}

err:
	class_dev_iter_exit(&iter);
	return ERR_PTR(ret);
}
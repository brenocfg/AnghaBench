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
struct pci_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct ce4100_devices {int /*<<< orphan*/ * pdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_i2c_device (struct pci_dev*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kfree (struct ce4100_devices*) ; 
 struct ce4100_devices* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ce4100_devices*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ce4100_i2c_probe(struct pci_dev *dev,
		const struct pci_device_id *ent)
{
	int ret;
	int i;
	struct ce4100_devices *sds;

	ret = pci_enable_device_mem(dev);
	if (ret)
		return ret;

	if (!dev->dev.of_node) {
		dev_err(&dev->dev, "Missing device tree node.\n");
		return -EINVAL;
	}
	sds = kzalloc(sizeof(*sds), GFP_KERNEL);
	if (!sds) {
		ret = -ENOMEM;
		goto err_mem;
	}

	for (i = 0; i < ARRAY_SIZE(sds->pdev); i++) {
		sds->pdev[i] = add_i2c_device(dev, i);
		if (IS_ERR(sds->pdev[i])) {
			ret = PTR_ERR(sds->pdev[i]);
			while (--i >= 0)
				platform_device_unregister(sds->pdev[i]);
			goto err_dev_add;
		}
	}
	pci_set_drvdata(dev, sds);
	return 0;

err_dev_add:
	kfree(sds);
err_mem:
	pci_disable_device(dev);
	return ret;
}
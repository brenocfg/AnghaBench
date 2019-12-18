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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct efa_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct efa_dev*) ; 
 int PTR_ERR (struct efa_dev*) ; 
 int efa_ib_device_add (struct efa_dev*) ; 
 struct efa_dev* efa_probe_device (struct pci_dev*) ; 
 int /*<<< orphan*/  efa_remove_device (struct pci_dev*) ; 

__attribute__((used)) static int efa_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct efa_dev *dev;
	int err;

	dev = efa_probe_device(pdev);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	err = efa_ib_device_add(dev);
	if (err)
		goto err_remove_device;

	return 0;

err_remove_device:
	efa_remove_device(pdev);
	return err;
}
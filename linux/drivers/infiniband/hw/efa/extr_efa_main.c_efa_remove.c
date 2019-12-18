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
struct pci_dev {int dummy; } ;
struct efa_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efa_ib_device_remove (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_remove_device (struct pci_dev*) ; 
 struct efa_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void efa_remove(struct pci_dev *pdev)
{
	struct efa_dev *dev = pci_get_drvdata(pdev);

	efa_ib_device_remove(dev);
	efa_remove_device(pdev);
}
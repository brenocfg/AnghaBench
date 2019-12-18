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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_hdev (struct hl_device*) ; 
 int /*<<< orphan*/  hl_device_fini (struct hl_device*) ; 
 struct hl_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hl_pci_remove(struct pci_dev *pdev)
{
	struct hl_device *hdev;

	hdev = pci_get_drvdata(pdev);
	if (!hdev)
		return;

	hl_device_fini(hdev);
	pci_set_drvdata(pdev, NULL);

	destroy_hdev(hdev);
}
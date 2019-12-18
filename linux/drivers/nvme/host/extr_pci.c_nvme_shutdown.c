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
struct nvme_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_disable_prepare_reset (struct nvme_dev*,int) ; 
 struct nvme_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void nvme_shutdown(struct pci_dev *pdev)
{
	struct nvme_dev *dev = pci_get_drvdata(pdev);
	nvme_disable_prepare_reset(dev, true);
}
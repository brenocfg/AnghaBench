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
struct nvkm_device_pci {int suspend; int /*<<< orphan*/  pdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 struct nvkm_device_pci* nvkm_device_pci (struct nvkm_device*) ; 
 int pci_enable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_device_pci_preinit(struct nvkm_device *device)
{
	struct nvkm_device_pci *pdev = nvkm_device_pci(device);
	if (pdev->suspend) {
		int ret = pci_enable_device(pdev->pdev);
		if (ret)
			return ret;
		pci_set_master(pdev->pdev);
		pdev->suspend = false;
	}
	return 0;
}
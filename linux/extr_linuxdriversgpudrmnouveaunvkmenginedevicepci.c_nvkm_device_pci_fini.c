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
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvkm_device_pci_fini(struct nvkm_device *device, bool suspend)
{
	struct nvkm_device_pci *pdev = nvkm_device_pci(device);
	if (suspend) {
		pci_disable_device(pdev->pdev);
		pdev->suspend = true;
	}
}
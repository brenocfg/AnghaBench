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
struct nvkm_device_pci {int /*<<< orphan*/  pdev; } ;
struct nvkm_device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 struct nvkm_device_pci* nvkm_device_pci (struct nvkm_device*) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static resource_size_t
nvkm_device_pci_resource_addr(struct nvkm_device *device, unsigned bar)
{
	struct nvkm_device_pci *pdev = nvkm_device_pci(device);
	return pci_resource_start(pdev->pdev, bar);
}
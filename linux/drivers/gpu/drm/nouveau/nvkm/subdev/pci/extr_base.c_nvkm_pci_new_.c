#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_pci_func {scalar_t__ msi_rearm; } ;
struct TYPE_6__ {int speed; int width; } ;
struct nvkm_pci {int irq; int msi; int /*<<< orphan*/  subdev; TYPE_4__* pdev; TYPE_2__ pcie; struct nvkm_pci_func const* func; } ;
struct nvkm_device {scalar_t__ type; int /*<<< orphan*/  cfgopt; int /*<<< orphan*/  chipset; TYPE_1__* func; } ;
struct TYPE_8__ {int device; } ;
struct TYPE_7__ {TYPE_4__* pdev; } ;
struct TYPE_5__ {TYPE_3__* (* pci ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NVKM_DEVICE_AGP ; 
 struct nvkm_pci* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_agp_ctor (struct nvkm_pci*) ; 
 int nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvkm_pci_func ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_enable_msi (TYPE_4__*) ; 
 TYPE_3__* stub1 (struct nvkm_device*) ; 

int
nvkm_pci_new_(const struct nvkm_pci_func *func, struct nvkm_device *device,
	      int index, struct nvkm_pci **ppci)
{
	struct nvkm_pci *pci;

	if (!(pci = *ppci = kzalloc(sizeof(**ppci), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_pci_func, device, index, &pci->subdev);
	pci->func = func;
	pci->pdev = device->func->pci(device)->pdev;
	pci->irq = -1;
	pci->pcie.speed = -1;
	pci->pcie.width = -1;

	if (device->type == NVKM_DEVICE_AGP)
		nvkm_agp_ctor(pci);

	switch (pci->pdev->device & 0x0ff0) {
	case 0x00f0:
	case 0x02e0:
		/* BR02? NFI how these would be handled yet exactly */
		break;
	default:
		switch (device->chipset) {
		case 0xaa:
			/* reported broken, nv also disable it */
			break;
		default:
			pci->msi = true;
			break;
		}
	}

#ifdef __BIG_ENDIAN
	pci->msi = false;
#endif

	pci->msi = nvkm_boolopt(device->cfgopt, "NvMSI", pci->msi);
	if (pci->msi && func->msi_rearm) {
		pci->msi = pci_enable_msi(pci->pdev) == 0;
		if (pci->msi)
			nvkm_debug(&pci->subdev, "MSI enabled\n");
	} else {
		pci->msi = false;
	}

	return 0;
}
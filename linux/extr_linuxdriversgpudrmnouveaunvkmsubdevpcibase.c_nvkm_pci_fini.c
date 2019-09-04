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
struct nvkm_subdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ bridge; } ;
struct nvkm_pci {TYPE_1__ agp; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_agp_fini (struct nvkm_pci*) ; 
 struct nvkm_pci* nvkm_pci (struct nvkm_subdev*) ; 

__attribute__((used)) static int
nvkm_pci_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_pci *pci = nvkm_pci(subdev);

	if (pci->agp.bridge)
		nvkm_agp_fini(pci);

	return 0;
}
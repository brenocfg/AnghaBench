#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct TYPE_6__ {int speed; int /*<<< orphan*/  width; } ;
struct nvkm_pci {TYPE_3__ pcie; TYPE_2__* func; struct nvkm_subdev subdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (struct nvkm_pci*) ;} ;
struct TYPE_5__ {TYPE_1__ pcie; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_pcie_get_max_version (struct nvkm_pci*) ; 
 int nvkm_pcie_get_version (struct nvkm_pci*) ; 
 int /*<<< orphan*/  nvkm_pcie_set_link (struct nvkm_pci*,int,int /*<<< orphan*/ ) ; 
 int nvkm_pcie_set_version (struct nvkm_pci*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_pci*) ; 

int
nvkm_pcie_init(struct nvkm_pci *pci)
{
	struct nvkm_subdev *subdev = &pci->subdev;
	int ret;

	/* raise pcie version first */
	ret = nvkm_pcie_get_version(pci);
	if (ret > 0) {
		int max_version = nvkm_pcie_get_max_version(pci);
		if (max_version > 0 && max_version > ret)
			ret = nvkm_pcie_set_version(pci, max_version);

		if (ret < max_version)
			nvkm_error(subdev, "couldn't raise version: %i\n", ret);
	}

	if (pci->func->pcie.init)
		pci->func->pcie.init(pci);

	if (pci->pcie.speed != -1)
		nvkm_pcie_set_link(pci, pci->pcie.speed, pci->pcie.width);

	return 0;
}
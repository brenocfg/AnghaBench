#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_pci {TYPE_2__* func; int /*<<< orphan*/  subdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_version ) (struct nvkm_pci*,int) ;} ;
struct TYPE_4__ {TYPE_1__ pcie; } ;

/* Variables and functions */
 int ENOSYS ; 
 int nvkm_pcie_get_version (struct nvkm_pci*) ; 
 int /*<<< orphan*/  nvkm_trace (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_pci*,int) ; 

__attribute__((used)) static int
nvkm_pcie_set_version(struct nvkm_pci *pci, int version)
{
	if (!pci->func->pcie.set_version)
		return -ENOSYS;

	nvkm_trace(&pci->subdev, "set to version %i\n", version);
	pci->func->pcie.set_version(pci, version);
	return nvkm_pcie_get_version(pci);
}
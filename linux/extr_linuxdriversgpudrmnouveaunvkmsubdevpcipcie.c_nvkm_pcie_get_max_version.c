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
struct nvkm_pci {TYPE_2__* func; } ;
struct TYPE_3__ {int (* version_supported ) (struct nvkm_pci*) ;} ;
struct TYPE_4__ {TYPE_1__ pcie; } ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct nvkm_pci*) ; 

__attribute__((used)) static int
nvkm_pcie_get_max_version(struct nvkm_pci *pci)
{
	if (!pci->func->pcie.version_supported)
		return -ENOSYS;

	return pci->func->pcie.version_supported(pci);
}
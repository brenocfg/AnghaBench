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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_pci {TYPE_1__ subdev; } ;

/* Variables and functions */
 int nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
gk104_pcie_version_supported(struct nvkm_pci *pci)
{
	return (nvkm_rd32(pci->subdev.device, 0x8c1c0) & 0x4) == 0x4 ? 2 : 1;
}
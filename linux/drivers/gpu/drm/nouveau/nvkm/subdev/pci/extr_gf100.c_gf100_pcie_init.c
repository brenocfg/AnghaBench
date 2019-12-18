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
struct nvkm_pci {int dummy; } ;

/* Variables and functions */
 scalar_t__ NVKM_PCIE_SPEED_5_0 ; 
 scalar_t__ g84_pcie_cur_speed (struct nvkm_pci*) ; 
 int /*<<< orphan*/  gf100_pcie_set_cap_speed (struct nvkm_pci*,int) ; 

int
gf100_pcie_init(struct nvkm_pci *pci)
{
	bool full_speed = g84_pcie_cur_speed(pci) == NVKM_PCIE_SPEED_5_0;
	gf100_pcie_set_cap_speed(pci, full_speed);
	return 0;
}
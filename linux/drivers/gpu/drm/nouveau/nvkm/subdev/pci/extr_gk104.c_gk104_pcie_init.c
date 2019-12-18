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
struct nvkm_subdev {int dummy; } ;
struct nvkm_pci {struct nvkm_subdev subdev; } ;
typedef  enum nvkm_pcie_speed { ____Placeholder_nvkm_pcie_speed } nvkm_pcie_speed ;

/* Variables and functions */
 int gf100_pcie_version (struct nvkm_pci*) ; 
 int gk104_pcie_cap_speed (struct nvkm_pci*) ; 
 int gk104_pcie_lnkctl_speed (struct nvkm_pci*) ; 
 int gk104_pcie_max_speed (struct nvkm_pci*) ; 
 int /*<<< orphan*/  gk104_pcie_set_cap_speed (struct nvkm_pci*,int) ; 
 int /*<<< orphan*/  gk104_pcie_set_lnkctl_speed (struct nvkm_pci*,int) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_trace (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*) ; 

__attribute__((used)) static int
gk104_pcie_init(struct nvkm_pci * pci)
{
	enum nvkm_pcie_speed lnkctl_speed, max_speed, cap_speed;
	struct nvkm_subdev *subdev = &pci->subdev;

	if (gf100_pcie_version(pci) < 2)
		return 0;

	lnkctl_speed = gk104_pcie_lnkctl_speed(pci);
	max_speed = gk104_pcie_max_speed(pci);
	cap_speed = gk104_pcie_cap_speed(pci);

	if (cap_speed != max_speed) {
		nvkm_trace(subdev, "adjusting cap to max speed\n");
		gk104_pcie_set_cap_speed(pci, max_speed);
		cap_speed = gk104_pcie_cap_speed(pci);
		if (cap_speed != max_speed)
			nvkm_warn(subdev, "failed to adjust cap speed\n");
	}

	if (lnkctl_speed != max_speed) {
		nvkm_debug(subdev, "adjusting lnkctl to max speed\n");
		gk104_pcie_set_lnkctl_speed(pci, max_speed);
		lnkctl_speed = gk104_pcie_lnkctl_speed(pci);
		if (lnkctl_speed != max_speed)
			nvkm_error(subdev, "failed to adjust lnkctl speed\n");
	}

	return 0;
}
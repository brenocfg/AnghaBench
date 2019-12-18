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
struct TYPE_4__ {int pcie_gen_mask; } ;
struct amdgpu_device {TYPE_2__ pm; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 ; 
 int CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 ; 
 scalar_t__ amdgpu_pcie_gen2 ; 
 scalar_t__ pci_is_root_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv_pcie_gen3_enable(struct amdgpu_device *adev)
{
	if (pci_is_root_bus(adev->pdev->bus))
		return;

	if (amdgpu_pcie_gen2 == 0)
		return;

	if (!(adev->pm.pcie_gen_mask & (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
					CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)))
		return;

	/* todo */
}
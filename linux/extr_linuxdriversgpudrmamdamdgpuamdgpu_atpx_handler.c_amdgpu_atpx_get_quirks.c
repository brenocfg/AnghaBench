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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;
struct amdgpu_px_quirk {scalar_t__ chip_device; scalar_t__ chip_vendor; scalar_t__ subsys_vendor; scalar_t__ subsys_device; int /*<<< orphan*/  px_quirk_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 TYPE_1__ amdgpu_atpx_priv ; 
 struct amdgpu_px_quirk* amdgpu_px_quirk_list ; 

__attribute__((used)) static void amdgpu_atpx_get_quirks(struct pci_dev *pdev)
{
	const struct amdgpu_px_quirk *p = amdgpu_px_quirk_list;

	/* Apply PX quirks */
	while (p && p->chip_device != 0) {
		if (pdev->vendor == p->chip_vendor &&
		    pdev->device == p->chip_device &&
		    pdev->subsystem_vendor == p->subsys_vendor &&
		    pdev->subsystem_device == p->subsys_device) {
			amdgpu_atpx_priv.quirks |= p->px_quirk_flags;
			break;
		}
		++p;
	}
}
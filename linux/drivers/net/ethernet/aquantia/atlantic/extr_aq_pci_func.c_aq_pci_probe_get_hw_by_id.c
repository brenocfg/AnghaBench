#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ vendor; scalar_t__ device; scalar_t__ revision; } ;
struct aq_hw_ops {int dummy; } ;
struct aq_hw_caps_s {int dummy; } ;
struct TYPE_3__ {scalar_t__ devid; scalar_t__ revision; struct aq_hw_caps_s* caps; struct aq_hw_ops* ops; } ;

/* Variables and functions */
 scalar_t__ AQ_HWREV_ANY ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ PCI_VENDOR_ID_AQUANTIA ; 
 TYPE_1__* hw_atl_boards ; 

__attribute__((used)) static int aq_pci_probe_get_hw_by_id(struct pci_dev *pdev,
				     const struct aq_hw_ops **ops,
				     const struct aq_hw_caps_s **caps)
{
	int i;

	if (pdev->vendor != PCI_VENDOR_ID_AQUANTIA)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(hw_atl_boards); i++) {
		if (hw_atl_boards[i].devid == pdev->device &&
		    (hw_atl_boards[i].revision == AQ_HWREV_ANY ||
		     hw_atl_boards[i].revision == pdev->revision)) {
			*ops = hw_atl_boards[i].ops;
			*caps = hw_atl_boards[i].caps;
			break;
		}
	}

	if (i == ARRAY_SIZE(hw_atl_boards))
		return -EINVAL;

	return 0;
}
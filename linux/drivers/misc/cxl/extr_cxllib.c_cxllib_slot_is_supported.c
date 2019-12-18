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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int cxl_calc_capp_routing (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxl_is_power9 () ; 
 scalar_t__ cxl_slot_is_switched (struct pci_dev*) ; 

bool cxllib_slot_is_supported(struct pci_dev *dev, unsigned long flags)
{
	int rc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	/* No flags currently supported */
	if (flags)
		return false;

	if (!cpu_has_feature(CPU_FTR_HVMODE))
		return false;

	if (!cxl_is_power9())
		return false;

	if (cxl_slot_is_switched(dev))
		return false;

	/* on p9, some pci slots are not connected to a CAPP unit */
	rc = cxl_calc_capp_routing(dev, &chip_id, &phb_index, &capp_unit_id);
	if (rc)
		return false;

	return true;
}
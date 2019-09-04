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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {scalar_t__ t4_bar0; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 scalar_t__ t4_read_pcie_cfg4 (struct adapter*,scalar_t__) ; 

__attribute__((used)) static u32 t4_get_window(struct adapter *adap, u32 pci_base, u64 pci_mask,
			 u32 memwin_base)
{
	u32 ret;

	if (is_t4(adap->params.chip)) {
		u32 bar0;

		/* Truncation intentional: we only read the bottom 32-bits of
		 * the 64-bit BAR0/BAR1 ...  We use the hardware backdoor
		 * mechanism to read BAR0 instead of using
		 * pci_resource_start() because we could be operating from
		 * within a Virtual Machine which is trapping our accesses to
		 * our Configuration Space and we need to set up the PCI-E
		 * Memory Window decoders with the actual addresses which will
		 * be coming across the PCI-E link.
		 */
		bar0 = t4_read_pcie_cfg4(adap, pci_base);
		bar0 &= pci_mask;
		adap->t4_bar0 = bar0;

		ret = bar0 + memwin_base;
	} else {
		/* For T5, only relative offset inside the PCIe BAR is passed */
		ret = memwin_base;
	}
	return ret;
}
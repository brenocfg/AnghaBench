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
struct pci_dev {int /*<<< orphan*/  subordinate; scalar_t__ d3cold_delay; int /*<<< orphan*/  imm_ready; scalar_t__ runtime_d3cold; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 scalar_t__ PCI_D0 ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  pci_platform_power_transition (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_wakeup_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pci_start_power_transition(struct pci_dev *dev, pci_power_t state)
{
	if (state == PCI_D0) {
		pci_platform_power_transition(dev, PCI_D0);
		/*
		 * Mandatory power management transition delays, see
		 * PCI Express Base Specification Revision 2.0 Section
		 * 6.6.1: Conventional Reset.  Do not delay for
		 * devices powered on/off by corresponding bridge,
		 * because have already delayed for the bridge.
		 */
		if (dev->runtime_d3cold) {
			if (dev->d3cold_delay && !dev->imm_ready)
				msleep(dev->d3cold_delay);
			/*
			 * When powering on a bridge from D3cold, the
			 * whole hierarchy may be powered on into
			 * D0uninitialized state, resume them to give
			 * them a chance to suspend again
			 */
			pci_wakeup_bus(dev->subordinate);
		}
	}
}
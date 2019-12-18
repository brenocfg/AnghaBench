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
struct controller {int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDICATOR_NOOP ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_OFF ; 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  atomic_and (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pciehp_power_off_slot (struct controller*) ; 
 int /*<<< orphan*/  pciehp_set_indicators (struct controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_unconfigure_device (struct controller*,int) ; 

__attribute__((used)) static void remove_board(struct controller *ctrl, bool safe_removal)
{
	pciehp_unconfigure_device(ctrl, safe_removal);

	if (POWER_CTRL(ctrl)) {
		pciehp_power_off_slot(ctrl);

		/*
		 * After turning power off, we must wait for at least 1 second
		 * before taking any action that relies on power having been
		 * removed from the slot/adapter.
		 */
		msleep(1000);

		/* Ignore link or presence changes caused by power off */
		atomic_and(~(PCI_EXP_SLTSTA_DLLSC | PCI_EXP_SLTSTA_PDC),
			   &ctrl->pending_events);
	}

	pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
			      INDICATOR_NOOP);
}
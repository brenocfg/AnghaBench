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
struct pci_dev {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ CHV_DEVICE_ID ; 
 int /*<<< orphan*/  pm_suspend_via_firmware () ; 

__attribute__((used)) static inline bool ish_should_enter_d0i3(struct pci_dev *pdev)
{
	return !pm_suspend_via_firmware() || pdev->device == CHV_DEVICE_ID;
}
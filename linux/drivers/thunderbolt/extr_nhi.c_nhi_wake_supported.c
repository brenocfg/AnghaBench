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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_property_read_u8 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nhi_wake_supported(struct pci_dev *pdev)
{
	u8 val;

	/*
	 * If power rails are sustainable for wakeup from S4 this
	 * property is set by the BIOS.
	 */
	if (device_property_read_u8(&pdev->dev, "WAKE_SUPPORTED", &val))
		return !!val;

	return true;
}
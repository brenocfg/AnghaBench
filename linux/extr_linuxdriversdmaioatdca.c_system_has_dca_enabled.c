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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_DCA ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int dca_enabled_in_bios (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

int system_has_dca_enabled(struct pci_dev *pdev)
{
	if (boot_cpu_has(X86_FEATURE_DCA))
		return dca_enabled_in_bios(pdev);

	dev_dbg(&pdev->dev, "boot cpu doesn't have X86_FEATURE_DCA\n");
	return 0;
}
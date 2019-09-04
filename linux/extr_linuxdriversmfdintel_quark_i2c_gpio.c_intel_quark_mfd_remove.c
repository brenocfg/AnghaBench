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
 int /*<<< orphan*/  intel_quark_unregister_i2c_clk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_quark_mfd_remove(struct pci_dev *pdev)
{
	intel_quark_unregister_i2c_clk(&pdev->dev);
	mfd_remove_devices(&pdev->dev);
}
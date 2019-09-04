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
 int /*<<< orphan*/  __e1000_shutdown (struct pci_dev*,int) ; 
 int /*<<< orphan*/  e1000e_flush_lpic (struct pci_dev*) ; 
 int /*<<< orphan*/  e1000e_pm_freeze (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_shutdown(struct pci_dev *pdev)
{
	e1000e_flush_lpic(pdev);

	e1000e_pm_freeze(&pdev->dev);

	__e1000_shutdown(pdev, false);
}
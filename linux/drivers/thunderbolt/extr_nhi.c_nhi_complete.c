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
struct tb {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tb* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_resume (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_domain_complete (struct tb*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void nhi_complete(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct tb *tb = pci_get_drvdata(pdev);

	/*
	 * If we were runtime suspended when system suspend started,
	 * schedule runtime resume now. It should bring the domain back
	 * to functional state.
	 */
	if (pm_runtime_suspended(&pdev->dev))
		pm_runtime_resume(&pdev->dev);
	else
		tb_domain_complete(tb);
}
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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,...) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_note_irq_problem(struct pci_dev *pdev, const char *reason)
{
	struct pci_dev *parent = to_pci_dev(pdev->dev.parent);

	pci_err(pdev, "Potentially misrouted IRQ (Bridge %s %04x:%04x)\n",
		dev_name(&parent->dev), parent->vendor, parent->device);
	pci_err(pdev, "%s\n", reason);
	pci_err(pdev, "Please report to linux-kernel@vger.kernel.org\n");
	WARN_ON(1);
}
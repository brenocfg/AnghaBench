#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct intel_uncore {int /*<<< orphan*/  regs; TYPE_2__* i915; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uncore_mmio_cleanup(struct intel_uncore *uncore)
{
	struct pci_dev *pdev = uncore->i915->drm.pdev;

	pci_iounmap(pdev, uncore->regs);
}
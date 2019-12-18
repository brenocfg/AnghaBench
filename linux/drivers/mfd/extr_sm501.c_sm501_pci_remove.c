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
struct sm501_devdata {int /*<<< orphan*/  regs_claim; int /*<<< orphan*/  regs; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct sm501_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_dev_remove (struct sm501_devdata*) ; 

__attribute__((used)) static void sm501_pci_remove(struct pci_dev *dev)
{
	struct sm501_devdata *sm = pci_get_drvdata(dev);

	sm501_dev_remove(sm);
	iounmap(sm->regs);

	release_resource(sm->regs_claim);
	kfree(sm->regs_claim);

	pci_disable_device(dev);
}
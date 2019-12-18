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
struct pci_dev {int dummy; } ;
struct emu {int /*<<< orphan*/  size; int /*<<< orphan*/  io; int /*<<< orphan*/  gameport; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct emu*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct emu* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emu_remove(struct pci_dev *pdev)
{
	struct emu *emu = pci_get_drvdata(pdev);

	gameport_unregister_port(emu->gameport);
	release_region(emu->io, emu->size);
	kfree(emu);

	pci_disable_device(pdev);
}
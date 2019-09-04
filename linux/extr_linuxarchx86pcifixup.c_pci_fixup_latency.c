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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int pcibios_max_latency ; 

__attribute__((used)) static void pci_fixup_latency(struct pci_dev *d)
{
	/*
	 *  SiS 5597 and 5598 chipsets require latency timer set to
	 *  at most 32 to avoid lockups.
	 */
	dev_dbg(&d->dev, "Setting max latency to 32\n");
	pcibios_max_latency = 32;
}
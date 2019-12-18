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
struct resource {int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  parent; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_UNSET ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,struct resource*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 scalar_t__ resource_size (struct resource*) ; 

void pci_release_resource(struct pci_dev *dev, int resno)
{
	struct resource *res = dev->resource + resno;

	pci_info(dev, "BAR %d: releasing %pR\n", resno, res);

	if (!res->parent)
		return;

	release_resource(res);
	res->end = resource_size(res) - 1;
	res->start = 0;
	res->flags |= IORESOURCE_UNSET;
}
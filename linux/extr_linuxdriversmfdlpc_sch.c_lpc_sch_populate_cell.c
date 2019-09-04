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
struct resource {int start; int end; int /*<<< orphan*/  flags; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mfd_cell {char const* name; int num_resources; int ignore_resource_conflicts; int id; struct resource* resources; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 struct resource* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int lpc_sch_get_io (struct pci_dev*,int,char const*,struct resource*,int) ; 
 int /*<<< orphan*/  memset (struct mfd_cell*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpc_sch_populate_cell(struct pci_dev *pdev, int where,
				 const char *name, int size, int irq,
				 int id, struct mfd_cell *cell)
{
	struct resource *res;
	int ret;

	res = devm_kcalloc(&pdev->dev, 2, sizeof(*res), GFP_KERNEL);
	if (!res)
		return -ENOMEM;

	ret = lpc_sch_get_io(pdev, where, name, res, size);
	if (ret)
		return ret;

	memset(cell, 0, sizeof(*cell));

	cell->name = name;
	cell->resources = res;
	cell->num_resources = 1;
	cell->ignore_resource_conflicts = true;
	cell->id = id;

	/* Check if we need to add an IRQ resource */
	if (irq < 0)
		return 0;

	res++;

	res->start = irq;
	res->end = irq;
	res->flags = IORESOURCE_IRQ;

	cell->num_resources++;

	return 0;
}
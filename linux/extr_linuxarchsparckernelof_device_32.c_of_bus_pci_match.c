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
struct device_node {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int of_bus_pci_match(struct device_node *np)
{
	if (!strcmp(np->type, "pci") || !strcmp(np->type, "pciex")) {
		/* Do not do PCI specific frobbing if the
		 * PCI bridge lacks a ranges property.  We
		 * want to pass it through up to the next
		 * parent as-is, not with the PCI translate
		 * method which chops off the top address cell.
		 */
		if (!of_find_property(np, "ranges", NULL))
			return 0;

		return 1;
	}

	return 0;
}
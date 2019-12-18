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
struct resource_entry {int /*<<< orphan*/  offset; } ;
struct resource {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,struct resource*) ; 
 int /*<<< orphan*/  resource_list_add_tail (struct resource_entry*,struct list_head*) ; 
 struct resource_entry* resource_list_create_entry (struct resource*,int /*<<< orphan*/ ) ; 

void pci_add_resource_offset(struct list_head *resources, struct resource *res,
			     resource_size_t offset)
{
	struct resource_entry *entry;

	entry = resource_list_create_entry(res, 0);
	if (!entry) {
		pr_err("PCI: can't add host bridge window %pR\n", res);
		return;
	}

	entry->offset = offset;
	resource_list_add_tail(entry, resources);
}
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
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct pci_dev_resource {int /*<<< orphan*/  list; void* min_align; void* add_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct pci_dev* dev; struct resource* res; } ;
struct pci_dev {int dummy; } ;
struct list_head {int dummy; } ;
typedef  void* resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pci_dev_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int add_to_list(struct list_head *head, struct pci_dev *dev,
		       struct resource *res, resource_size_t add_size,
		       resource_size_t min_align)
{
	struct pci_dev_resource *tmp;

	tmp = kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	tmp->res = res;
	tmp->dev = dev;
	tmp->start = res->start;
	tmp->end = res->end;
	tmp->flags = res->flags;
	tmp->add_size = add_size;
	tmp->min_align = min_align;

	list_add(&tmp->list, head);

	return 0;
}
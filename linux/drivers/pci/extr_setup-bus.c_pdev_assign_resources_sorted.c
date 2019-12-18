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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __assign_resources_sorted (int /*<<< orphan*/ *,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  __dev_sort_resources (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head ; 

__attribute__((used)) static void pdev_assign_resources_sorted(struct pci_dev *dev,
					 struct list_head *add_head,
					 struct list_head *fail_head)
{
	LIST_HEAD(head);

	__dev_sort_resources(dev, &head);
	__assign_resources_sorted(&head, add_head, fail_head);

}
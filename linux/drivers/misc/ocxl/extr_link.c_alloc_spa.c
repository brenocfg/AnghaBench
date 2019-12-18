#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fault_work; } ;
struct spa {struct ocxl_process_element* spa_mem; scalar_t__ spa_order; TYPE_1__ xsl_fault; int /*<<< orphan*/  pe_tree; int /*<<< orphan*/  spa_lock; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_process_element {int dummy; } ;
struct ocxl_link {struct spa* spa; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ SPA_SPA_SIZE_LOG ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct spa*) ; 
 struct spa* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocxl_process_element*) ; 
 int /*<<< orphan*/  xsl_fault_handler_bh ; 

__attribute__((used)) static int alloc_spa(struct pci_dev *dev, struct ocxl_link *link)
{
	struct spa *spa;

	spa = kzalloc(sizeof(struct spa), GFP_KERNEL);
	if (!spa)
		return -ENOMEM;

	mutex_init(&spa->spa_lock);
	INIT_RADIX_TREE(&spa->pe_tree, GFP_KERNEL);
	INIT_WORK(&spa->xsl_fault.fault_work, xsl_fault_handler_bh);

	spa->spa_order = SPA_SPA_SIZE_LOG - PAGE_SHIFT;
	spa->spa_mem = (struct ocxl_process_element *)
		__get_free_pages(GFP_KERNEL | __GFP_ZERO, spa->spa_order);
	if (!spa->spa_mem) {
		dev_err(&dev->dev, "Can't allocate Shared Process Area\n");
		kfree(spa);
		return -ENOMEM;
	}
	pr_debug("Allocated SPA for %x:%x:%x at %p\n", link->domain, link->bus,
		link->dev, spa->spa_mem);

	link->spa = spa;
	return 0;
}
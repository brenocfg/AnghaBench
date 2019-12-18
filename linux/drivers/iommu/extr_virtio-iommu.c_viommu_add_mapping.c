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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long start; unsigned long last; } ;
struct viommu_mapping {TYPE_1__ iova; int /*<<< orphan*/  flags; int /*<<< orphan*/  paddr; } ;
struct viommu_domain {int /*<<< orphan*/  mappings_lock; int /*<<< orphan*/  mappings; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  interval_tree_insert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct viommu_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int viommu_add_mapping(struct viommu_domain *vdomain, unsigned long iova,
			      phys_addr_t paddr, size_t size, u32 flags)
{
	unsigned long irqflags;
	struct viommu_mapping *mapping;

	mapping = kzalloc(sizeof(*mapping), GFP_ATOMIC);
	if (!mapping)
		return -ENOMEM;

	mapping->paddr		= paddr;
	mapping->iova.start	= iova;
	mapping->iova.last	= iova + size - 1;
	mapping->flags		= flags;

	spin_lock_irqsave(&vdomain->mappings_lock, irqflags);
	interval_tree_insert(&mapping->iova, &vdomain->mappings);
	spin_unlock_irqrestore(&vdomain->mappings_lock, irqflags);

	return 0;
}
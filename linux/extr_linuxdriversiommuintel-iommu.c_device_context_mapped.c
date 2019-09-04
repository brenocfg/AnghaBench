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
typedef  int /*<<< orphan*/  u8 ;
struct intel_iommu {int /*<<< orphan*/  lock; } ;
struct context_entry {int dummy; } ;

/* Variables and functions */
 int context_present (struct context_entry*) ; 
 struct context_entry* iommu_context_addr (struct intel_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int device_context_mapped(struct intel_iommu *iommu, u8 bus, u8 devfn)
{
	struct context_entry *context;
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&iommu->lock, flags);
	context = iommu_context_addr(iommu, bus, devfn, 0);
	if (context)
		ret = context_present(context);
	spin_unlock_irqrestore(&iommu->lock, flags);
	return ret;
}
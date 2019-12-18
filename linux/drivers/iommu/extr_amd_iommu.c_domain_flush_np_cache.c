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
struct protection_domain {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_np_cache ; 
 int /*<<< orphan*/  domain_flush_complete (struct protection_domain*) ; 
 int /*<<< orphan*/  domain_flush_pages (struct protection_domain*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void domain_flush_np_cache(struct protection_domain *domain,
		dma_addr_t iova, size_t size)
{
	if (unlikely(amd_iommu_np_cache)) {
		unsigned long flags;

		spin_lock_irqsave(&domain->lock, flags);
		domain_flush_pages(domain, iova, size);
		domain_flush_complete(domain);
		spin_unlock_irqrestore(&domain->lock, flags);
	}
}
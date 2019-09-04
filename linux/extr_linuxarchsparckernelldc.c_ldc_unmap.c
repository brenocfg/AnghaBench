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
typedef  int /*<<< orphan*/  u64 ;
struct ldc_trans_cookie {int /*<<< orphan*/  cookie_size; int /*<<< orphan*/  cookie_addr; } ;
struct ldc_iommu {int /*<<< orphan*/  lock; } ;
struct ldc_channel {int /*<<< orphan*/  id; struct ldc_iommu iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_npages (int /*<<< orphan*/ ,struct ldc_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ldc_unmap(struct ldc_channel *lp, struct ldc_trans_cookie *cookies,
	       int ncookies)
{
	struct ldc_iommu *iommu = &lp->iommu;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&iommu->lock, flags);
	for (i = 0; i < ncookies; i++) {
		u64 addr = cookies[i].cookie_addr;
		u64 size = cookies[i].cookie_size;

		free_npages(lp->id, iommu, addr, size);
	}
	spin_unlock_irqrestore(&iommu->lock, flags);
}
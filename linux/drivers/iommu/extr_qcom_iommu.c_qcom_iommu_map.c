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
struct qcom_iommu_domain {int /*<<< orphan*/  pgtbl_lock; struct io_pgtable_ops* pgtbl_ops; } ;
struct iommu_domain {int dummy; } ;
struct io_pgtable_ops {int (* map ) (struct io_pgtable_ops*,unsigned long,int /*<<< orphan*/ ,size_t,int) ;} ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct io_pgtable_ops*,unsigned long,int /*<<< orphan*/ ,size_t,int) ; 
 struct qcom_iommu_domain* to_qcom_iommu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int qcom_iommu_map(struct iommu_domain *domain, unsigned long iova,
			  phys_addr_t paddr, size_t size, int prot)
{
	int ret;
	unsigned long flags;
	struct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	struct io_pgtable_ops *ops = qcom_domain->pgtbl_ops;

	if (!ops)
		return -ENODEV;

	spin_lock_irqsave(&qcom_domain->pgtbl_lock, flags);
	ret = ops->map(ops, iova, paddr, size, prot);
	spin_unlock_irqrestore(&qcom_domain->pgtbl_lock, flags);
	return ret;
}
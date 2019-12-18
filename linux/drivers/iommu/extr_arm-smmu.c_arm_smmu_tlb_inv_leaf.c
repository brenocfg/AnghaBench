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
struct arm_smmu_flush_ops {int /*<<< orphan*/  (* tlb_sync ) (void*) ;int /*<<< orphan*/  (* tlb_inv_range ) (unsigned long,size_t,size_t,int,void*) ;} ;
struct arm_smmu_domain {struct arm_smmu_flush_ops* flush_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned long,size_t,size_t,int,void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void arm_smmu_tlb_inv_leaf(unsigned long iova, size_t size,
				  size_t granule, void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	const struct arm_smmu_flush_ops *ops = smmu_domain->flush_ops;

	ops->tlb_inv_range(iova, size, granule, true, cookie);
	ops->tlb_sync(cookie);
}
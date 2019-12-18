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
struct TYPE_2__ {int (* handler ) (int /*<<< orphan*/ ,unsigned long,int) ;int /*<<< orphan*/  arg; } ;
struct msm_iommu {TYPE_1__ base; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn_ratelimited (char*,unsigned long,int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int msm_fault_handler(struct iommu_domain *domain, struct device *dev,
		unsigned long iova, int flags, void *arg)
{
	struct msm_iommu *iommu = arg;
	if (iommu->base.handler)
		return iommu->base.handler(iommu->base.arg, iova, flags);
	pr_warn_ratelimited("*** fault: iova=%16lx, flags=%d\n", iova, flags);
	return 0;
}
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
struct rproc {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  RPROC_MMUFAULT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,int) ; 
 int /*<<< orphan*/  rproc_report_crash (struct rproc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rproc_iommu_fault(struct iommu_domain *domain, struct device *dev,
			     unsigned long iova, int flags, void *token)
{
	struct rproc *rproc = token;

	dev_err(dev, "iommu fault: da 0x%lx flags 0x%x\n", iova, flags);

	rproc_report_crash(rproc, RPROC_MMUFAULT);

	/*
	 * Let the iommu core know we're not really handling this fault;
	 * we just used it as a recovery trigger.
	 */
	return -ENOSYS;
}
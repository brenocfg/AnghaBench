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
struct viommu_dev {int /*<<< orphan*/  request_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __viommu_add_req (struct viommu_dev*,void*,size_t,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int viommu_add_req(struct viommu_dev *viommu, void *buf, size_t len)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&viommu->request_lock, flags);
	ret = __viommu_add_req(viommu, buf, len, false);
	if (ret)
		dev_dbg(viommu->dev, "could not add request: %d\n", ret);
	spin_unlock_irqrestore(&viommu->request_lock, flags);

	return ret;
}
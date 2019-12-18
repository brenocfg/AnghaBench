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
struct gart_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gart_debug ; 
 int /*<<< orphan*/  gart_pte_valid (struct gart_device*,unsigned long) ; 
 int /*<<< orphan*/  gart_set_pte (struct gart_device*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __gart_iommu_unmap(struct gart_device *gart,
				     unsigned long iova)
{
	if (unlikely(gart_debug && !gart_pte_valid(gart, iova))) {
		dev_err(gart->dev, "Page entry is invalid\n");
		return -EINVAL;
	}

	gart_set_pte(gart, iova, 0);

	return 0;
}
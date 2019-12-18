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
 unsigned long GART_ENTRY_PHYS_ADDR_VALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gart_debug ; 
 scalar_t__ gart_pte_valid (struct gart_device*,unsigned long) ; 
 int /*<<< orphan*/  gart_set_pte (struct gart_device*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __gart_iommu_map(struct gart_device *gart, unsigned long iova,
				   unsigned long pa)
{
	if (unlikely(gart_debug && gart_pte_valid(gart, iova))) {
		dev_err(gart->dev, "Page entry is in-use\n");
		return -EINVAL;
	}

	gart_set_pte(gart, iova, GART_ENTRY_PHYS_ADDR_VALID | pa);

	return 0;
}
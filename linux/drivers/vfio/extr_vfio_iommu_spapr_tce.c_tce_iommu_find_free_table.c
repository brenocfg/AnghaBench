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
struct tce_container {int /*<<< orphan*/ * tables; } ;

/* Variables and functions */
 int ENOSPC ; 
 int IOMMU_TABLE_GROUP_MAX_TABLES ; 

__attribute__((used)) static int tce_iommu_find_free_table(struct tce_container *container)
{
	int i;

	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) {
		if (!container->tables[i])
			return i;
	}

	return -ENOSPC;
}
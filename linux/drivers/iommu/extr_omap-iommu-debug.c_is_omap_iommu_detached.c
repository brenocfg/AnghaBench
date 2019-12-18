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
struct omap_iommu {int /*<<< orphan*/  domain; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_omap_iommu_detached(struct omap_iommu *obj)
{
	return !obj->domain;
}
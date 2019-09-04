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
struct dax_region {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  dax_region_attribute_groups ; 
 int /*<<< orphan*/  dax_region_put (struct dax_region*) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dax_region_unregister(void *region)
{
	struct dax_region *dax_region = region;

	sysfs_remove_groups(&dax_region->dev->kobj,
			dax_region_attribute_groups);
	dax_region_put(dax_region);
}
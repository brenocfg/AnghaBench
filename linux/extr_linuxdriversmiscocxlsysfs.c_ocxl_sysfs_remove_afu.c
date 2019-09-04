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
struct ocxl_afu {int /*<<< orphan*/  attr_global_mmio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * afu_attrs ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ocxl_sysfs_remove_afu(struct ocxl_afu *afu)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(afu_attrs); i++)
		device_remove_file(&afu->dev, &afu_attrs[i]);
	device_remove_bin_file(&afu->dev, &afu->attr_global_mmio);
}
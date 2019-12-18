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
struct ocxl_file_info {int /*<<< orphan*/  dev; } ;
struct ocxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 struct ocxl_file_info* ocxl_afu_get_private (struct ocxl_afu*) ; 
 int /*<<< orphan*/  ocxl_file_make_invisible (struct ocxl_file_info*) ; 
 int /*<<< orphan*/  ocxl_sysfs_unregister_afu (struct ocxl_file_info*) ; 

void ocxl_file_unregister_afu(struct ocxl_afu *afu)
{
	struct ocxl_file_info *info = ocxl_afu_get_private(afu);

	if (!info)
		return;

	ocxl_file_make_invisible(info);
	ocxl_sysfs_unregister_afu(info);
	device_unregister(&info->dev);
}
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
struct ocxl_afu {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_afu (struct ocxl_afu*) ; 
 int /*<<< orphan*/  deconfigure_afu (struct ocxl_afu*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_context_detach_all (struct ocxl_afu*) ; 
 int /*<<< orphan*/  ocxl_sysfs_remove_afu (struct ocxl_afu*) ; 

__attribute__((used)) static void remove_afu(struct ocxl_afu *afu)
{
	list_del(&afu->list);
	ocxl_context_detach_all(afu);
	deactivate_afu(afu);
	ocxl_sysfs_remove_afu(afu);
	deconfigure_afu(afu);
	device_unregister(&afu->dev);
}
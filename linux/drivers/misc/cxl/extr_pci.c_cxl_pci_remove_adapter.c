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
struct cxl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_data_cache_flush (struct cxl*) ; 
 int /*<<< orphan*/  cxl_debugfs_adapter_remove (struct cxl*) ; 
 int /*<<< orphan*/  cxl_deconfigure_adapter (struct cxl*) ; 
 int /*<<< orphan*/  cxl_sysfs_adapter_remove (struct cxl*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 

__attribute__((used)) static void cxl_pci_remove_adapter(struct cxl *adapter)
{
	pr_devel("cxl_remove_adapter\n");

	cxl_sysfs_adapter_remove(adapter);
	cxl_debugfs_adapter_remove(adapter);

	/*
	 * Flush adapter datacache as its about to be removed.
	 */
	cxl_data_cache_flush(adapter);

	cxl_deconfigure_adapter(adapter);

	device_unregister(&adapter->dev);
}
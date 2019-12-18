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
struct adapter {int flags; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int CXGB4_USING_MSI ; 
 int CXGB4_USING_MSIX ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int /*<<< orphan*/  t4_dump_version_info (struct adapter*) ; 

__attribute__((used)) static void print_adapter_info(struct adapter *adapter)
{
	/* Hardware/Firmware/etc. Version/Revision IDs */
	t4_dump_version_info(adapter);

	/* Software/Hardware configuration */
	dev_info(adapter->pdev_dev, "Configuration: %sNIC %s, %s capable\n",
		 is_offload(adapter) ? "R" : "",
		 ((adapter->flags & CXGB4_USING_MSIX) ? "MSI-X" :
		  (adapter->flags & CXGB4_USING_MSI) ? "MSI" : ""),
		 is_offload(adapter) ? "Offload" : "non-Offload");
}
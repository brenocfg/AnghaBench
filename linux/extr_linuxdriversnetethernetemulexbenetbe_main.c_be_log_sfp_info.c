#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vendor_pn; int /*<<< orphan*/  vendor_name; } ;
struct be_adapter {size_t phy_state; int /*<<< orphan*/  flags; TYPE_2__ phy; int /*<<< orphan*/  port_name; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_FLAGS_PHY_MISCONFIGURED ; 
 int be_cmd_query_sfp_info (struct be_adapter*) ; 
 int /*<<< orphan*/ * be_misconfig_evt_port_state ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_log_sfp_info(struct be_adapter *adapter)
{
	int status;

	status = be_cmd_query_sfp_info(adapter);
	if (!status) {
		dev_err(&adapter->pdev->dev,
			"Port %c: %s Vendor: %s part no: %s",
			adapter->port_name,
			be_misconfig_evt_port_state[adapter->phy_state],
			adapter->phy.vendor_name,
			adapter->phy.vendor_pn);
	}
	adapter->flags &= ~BE_FLAGS_PHY_MISCONFIGURED;
}
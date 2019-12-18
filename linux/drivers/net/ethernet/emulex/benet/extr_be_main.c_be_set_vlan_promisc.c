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
struct device {int dummy; } ;
struct be_adapter {int if_flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int BE_IF_FLAGS_VLAN_PROMISCUOUS ; 
 int /*<<< orphan*/  ON ; 
 int be_cmd_rx_filter (struct be_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 

__attribute__((used)) static int be_set_vlan_promisc(struct be_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;
	int status;

	if (adapter->if_flags & BE_IF_FLAGS_VLAN_PROMISCUOUS)
		return 0;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_VLAN_PROMISCUOUS, ON);
	if (!status) {
		dev_info(dev, "Enabled VLAN promiscuous mode\n");
		adapter->if_flags |= BE_IF_FLAGS_VLAN_PROMISCUOUS;
	} else {
		dev_err(dev, "Failed to enable VLAN promiscuous mode\n");
	}
	return status;
}
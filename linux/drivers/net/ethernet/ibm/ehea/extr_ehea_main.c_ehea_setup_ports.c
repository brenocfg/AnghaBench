#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ehea_adapter {TYPE_3__** port; TYPE_2__* ofdev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ehea_add_adapter_mr (struct ehea_adapter*) ; 
 int /*<<< orphan*/  ehea_remove_adapter_mr (struct ehea_adapter*) ; 
 TYPE_3__* ehea_setup_single_port (struct ehea_adapter*,int /*<<< orphan*/  const,struct device_node*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int ehea_setup_ports(struct ehea_adapter *adapter)
{
	struct device_node *lhea_dn;
	struct device_node *eth_dn = NULL;

	const u32 *dn_log_port_id;
	int i = 0;

	lhea_dn = adapter->ofdev->dev.of_node;
	while ((eth_dn = of_get_next_child(lhea_dn, eth_dn))) {

		dn_log_port_id = of_get_property(eth_dn, "ibm,hea-port-no",
						 NULL);
		if (!dn_log_port_id) {
			pr_err("bad device node: eth_dn name=%pOF\n", eth_dn);
			continue;
		}

		if (ehea_add_adapter_mr(adapter)) {
			pr_err("creating MR failed\n");
			of_node_put(eth_dn);
			return -EIO;
		}

		adapter->port[i] = ehea_setup_single_port(adapter,
							  *dn_log_port_id,
							  eth_dn);
		if (adapter->port[i])
			netdev_info(adapter->port[i]->netdev,
				    "logical port id #%d\n", *dn_log_port_id);
		else
			ehea_remove_adapter_mr(adapter);

		i++;
	}
	return 0;
}
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
typedef  scalar_t__ const u32 ;
struct ehea_adapter {TYPE_2__* ofdev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 scalar_t__* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device_node *ehea_get_eth_dn(struct ehea_adapter *adapter,
					   u32 logical_port_id)
{
	struct device_node *lhea_dn;
	struct device_node *eth_dn = NULL;
	const u32 *dn_log_port_id;

	lhea_dn = adapter->ofdev->dev.of_node;
	while ((eth_dn = of_get_next_child(lhea_dn, eth_dn))) {

		dn_log_port_id = of_get_property(eth_dn, "ibm,hea-port-no",
						 NULL);
		if (dn_log_port_id)
			if (*dn_log_port_id == logical_port_id)
				return eth_dn;
	}

	return NULL;
}
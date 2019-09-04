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
struct mvpp2 {scalar_t__ hw_version; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 

__attribute__((used)) static bool mvpp2_port_has_tx_irqs(struct mvpp2 *priv,
				   struct device_node *port_node)
{
	char *irqs[5] = { "rx-shared", "tx-cpu0", "tx-cpu1",
			  "tx-cpu2", "tx-cpu3" };
	int ret, i;

	if (priv->hw_version == MVPP21)
		return false;

	for (i = 0; i < 5; i++) {
		ret = of_property_match_string(port_node, "interrupt-names",
					       irqs[i]);
		if (ret < 0)
			return false;
	}

	return true;
}
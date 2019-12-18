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
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned long MVPP2_F_DT_COMPAT ; 
 scalar_t__ of_property_match_string (struct device_node*,char*,char*) ; 

__attribute__((used)) static bool mvpp22_port_has_legacy_tx_irqs(struct device_node *port_node,
					   unsigned long *flags)
{
	char *irqs[5] = { "rx-shared", "tx-cpu0", "tx-cpu1", "tx-cpu2",
			  "tx-cpu3" };
	int i;

	for (i = 0; i < 5; i++)
		if (of_property_match_string(port_node, "interrupt-names",
					     irqs[i]) < 0)
			return false;

	*flags |= MVPP2_F_DT_COMPAT;
	return true;
}
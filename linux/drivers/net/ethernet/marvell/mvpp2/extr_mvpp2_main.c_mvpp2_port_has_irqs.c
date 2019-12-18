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
 int MVPP2_MAX_THREADS ; 
 scalar_t__ mvpp22_port_has_legacy_tx_irqs (struct device_node*,unsigned long*) ; 
 scalar_t__ of_property_match_string (struct device_node*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static bool mvpp2_port_has_irqs(struct mvpp2 *priv,
				struct device_node *port_node,
				unsigned long *flags)
{
	char name[5];
	int i;

	/* ACPI */
	if (!port_node)
		return true;

	if (priv->hw_version == MVPP21)
		return false;

	if (mvpp22_port_has_legacy_tx_irqs(port_node, flags))
		return true;

	for (i = 0; i < MVPP2_MAX_THREADS; i++) {
		snprintf(name, 5, "hif%d", i);
		if (of_property_match_string(port_node, "interrupt-names",
					     name) < 0)
			return false;
	}

	return true;
}
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
struct ehea_port {int logical_port_id; } ;
struct ehea_adapter {struct ehea_port** port; } ;

/* Variables and functions */
 int EHEA_MAX_PORTS ; 

__attribute__((used)) static struct ehea_port *ehea_get_port(struct ehea_adapter *adapter,
				       int logical_port)
{
	int i;

	for (i = 0; i < EHEA_MAX_PORTS; i++)
		if (adapter->port[i])
			if (adapter->port[i]->logical_port_id == logical_port)
				return adapter->port[i];
	return NULL;
}
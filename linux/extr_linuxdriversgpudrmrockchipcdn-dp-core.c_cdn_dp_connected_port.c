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
struct cdn_dp_port {int dummy; } ;
struct cdn_dp_device {int ports; struct cdn_dp_port** port; } ;

/* Variables and functions */
 int cdn_dp_get_port_lanes (struct cdn_dp_port*) ; 

__attribute__((used)) static struct cdn_dp_port *cdn_dp_connected_port(struct cdn_dp_device *dp)
{
	struct cdn_dp_port *port;
	int i, lanes;

	for (i = 0; i < dp->ports; i++) {
		port = dp->port[i];
		lanes = cdn_dp_get_port_lanes(port);
		if (lanes)
			return port;
	}
	return NULL;
}
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
struct ocelot_port {int chip_port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int ocelot_port_get_phys_port_name(struct net_device *dev,
					  char *buf, size_t len)
{
	struct ocelot_port *port = netdev_priv(dev);
	int ret;

	ret = snprintf(buf, len, "p%d", port->chip_port);
	if (ret >= len)
		return -EINVAL;

	return 0;
}
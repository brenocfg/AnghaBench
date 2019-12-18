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
struct ocelot_port {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 128 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int ocelot_setup_tc_block (struct ocelot_port*,void*) ; 

int ocelot_setup_tc(struct net_device *dev, enum tc_setup_type type,
		    void *type_data)
{
	struct ocelot_port *port = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return ocelot_setup_tc_block(port, type_data);
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}
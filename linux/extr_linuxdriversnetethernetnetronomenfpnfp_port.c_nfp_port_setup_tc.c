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
struct nfp_port {int /*<<< orphan*/  app; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int nfp_app_setup_tc (int /*<<< orphan*/ ,struct net_device*,int,void*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

int nfp_port_setup_tc(struct net_device *netdev, enum tc_setup_type type,
		      void *type_data)
{
	struct nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	if (!port)
		return -EOPNOTSUPP;

	return nfp_app_setup_tc(port->app, netdev, type, type_data);
}
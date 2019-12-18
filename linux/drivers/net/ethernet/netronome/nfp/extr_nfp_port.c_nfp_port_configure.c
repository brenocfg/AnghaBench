#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_port {TYPE_1__* app; scalar_t__ eth_forced; } ;
struct nfp_eth_table_port {int /*<<< orphan*/  index; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct nfp_eth_table_port* __nfp_port_get_eth_port (struct nfp_port*) ; 
 int nfp_eth_set_configured (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

int nfp_port_configure(struct net_device *netdev, bool configed)
{
	struct nfp_eth_table_port *eth_port;
	struct nfp_port *port;
	int err;

	port = nfp_port_from_netdev(netdev);
	eth_port = __nfp_port_get_eth_port(port);
	if (!eth_port)
		return 0;
	if (port->eth_forced)
		return 0;

	err = nfp_eth_set_configured(port->app->cpp, eth_port->index, configed);
	return err < 0 && err != -EOPNOTSUPP ? err : 0;
}
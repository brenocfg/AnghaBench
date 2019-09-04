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
struct nfp_repr {int /*<<< orphan*/  app_priv; } ;
struct nfp_port {scalar_t__ type; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NFP_PORT_PF_PORT ; 
#define  TC_SETUP_QDISC_MQ 129 
#define  TC_SETUP_QDISC_RED 128 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int nfp_abm_setup_tc_mq (struct net_device*,int /*<<< orphan*/ ,void*) ; 
 int nfp_abm_setup_tc_red (struct net_device*,int /*<<< orphan*/ ,void*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

__attribute__((used)) static int
nfp_abm_setup_tc(struct nfp_app *app, struct net_device *netdev,
		 enum tc_setup_type type, void *type_data)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	struct nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	if (!port || port->type != NFP_PORT_PF_PORT)
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_QDISC_MQ:
		return nfp_abm_setup_tc_mq(netdev, repr->app_priv, type_data);
	case TC_SETUP_QDISC_RED:
		return nfp_abm_setup_tc_red(netdev, repr->app_priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}
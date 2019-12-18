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
struct nfp_port {int type; int pf_id; int pf_split_id; int vf_id; int /*<<< orphan*/  pf_split; } ;
struct nfp_eth_table_port {int label_port; int label_subport; int /*<<< orphan*/  is_split; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  NFP_PORT_PF_PORT 130 
#define  NFP_PORT_PHYS_PORT 129 
#define  NFP_PORT_VF_PORT 128 
 struct nfp_eth_table_port* __nfp_port_get_eth_port (struct nfp_port*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int,...) ; 

int
nfp_port_get_phys_port_name(struct net_device *netdev, char *name, size_t len)
{
	struct nfp_eth_table_port *eth_port;
	struct nfp_port *port;
	int n;

	port = nfp_port_from_netdev(netdev);
	if (!port)
		return -EOPNOTSUPP;

	switch (port->type) {
	case NFP_PORT_PHYS_PORT:
		eth_port = __nfp_port_get_eth_port(port);
		if (!eth_port)
			return -EOPNOTSUPP;

		if (!eth_port->is_split)
			n = snprintf(name, len, "p%d", eth_port->label_port);
		else
			n = snprintf(name, len, "p%ds%d", eth_port->label_port,
				     eth_port->label_subport);
		break;
	case NFP_PORT_PF_PORT:
		if (!port->pf_split)
			n = snprintf(name, len, "pf%d", port->pf_id);
		else
			n = snprintf(name, len, "pf%ds%d", port->pf_id,
				     port->pf_split_id);
		break;
	case NFP_PORT_VF_PORT:
		n = snprintf(name, len, "pf%dvf%d", port->pf_id, port->vf_id);
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (n >= len)
		return -EINVAL;

	return 0;
}
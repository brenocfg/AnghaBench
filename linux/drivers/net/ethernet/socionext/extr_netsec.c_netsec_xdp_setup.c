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
struct netsec_priv {int /*<<< orphan*/  xdp_prog; struct net_device* ndev; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int mtu; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netsec_netdev_open (struct net_device*) ; 
 int /*<<< orphan*/  netsec_netdev_stop (struct net_device*) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,struct bpf_prog*) ; 

__attribute__((used)) static int netsec_xdp_setup(struct netsec_priv *priv, struct bpf_prog *prog,
			    struct netlink_ext_ack *extack)
{
	struct net_device *dev = priv->ndev;
	struct bpf_prog *old_prog;

	/* For now just support only the usual MTU sized frames */
	if (prog && dev->mtu > 1500) {
		NL_SET_ERR_MSG_MOD(extack, "Jumbo frames not supported on XDP");
		return -EOPNOTSUPP;
	}

	if (netif_running(dev))
		netsec_netdev_stop(dev);

	/* Detach old prog, if any */
	old_prog = xchg(&priv->xdp_prog, prog);
	if (old_prog)
		bpf_prog_put(old_prog);

	if (netif_running(dev))
		netsec_netdev_open(dev);

	return 0;
}
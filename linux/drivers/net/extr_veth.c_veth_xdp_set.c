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
struct veth_priv {struct bpf_prog* _xdp_prog; int /*<<< orphan*/  peer; } ;
struct skb_shared_info {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {unsigned int hard_header_len; unsigned int mtu; scalar_t__ real_num_rx_queues; scalar_t__ real_num_tx_queues; int flags; unsigned int max_mtu; int /*<<< orphan*/  hw_features; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int ENOTCONN ; 
 int ERANGE ; 
 unsigned int ETH_MAX_MTU ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NETIF_F_GSO_SOFTWARE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 unsigned int PAGE_SIZE ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 unsigned int VETH_XDP_HEADROOM ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_disable_xdp (struct net_device*) ; 
 int veth_enable_xdp (struct net_device*) ; 

__attribute__((used)) static int veth_xdp_set(struct net_device *dev, struct bpf_prog *prog,
			struct netlink_ext_ack *extack)
{
	struct veth_priv *priv = netdev_priv(dev);
	struct bpf_prog *old_prog;
	struct net_device *peer;
	unsigned int max_mtu;
	int err;

	old_prog = priv->_xdp_prog;
	priv->_xdp_prog = prog;
	peer = rtnl_dereference(priv->peer);

	if (prog) {
		if (!peer) {
			NL_SET_ERR_MSG_MOD(extack, "Cannot set XDP when peer is detached");
			err = -ENOTCONN;
			goto err;
		}

		max_mtu = PAGE_SIZE - VETH_XDP_HEADROOM -
			  peer->hard_header_len -
			  SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
		if (peer->mtu > max_mtu) {
			NL_SET_ERR_MSG_MOD(extack, "Peer MTU is too large to set XDP");
			err = -ERANGE;
			goto err;
		}

		if (dev->real_num_rx_queues < peer->real_num_tx_queues) {
			NL_SET_ERR_MSG_MOD(extack, "XDP expects number of rx queues not less than peer tx queues");
			err = -ENOSPC;
			goto err;
		}

		if (dev->flags & IFF_UP) {
			err = veth_enable_xdp(dev);
			if (err) {
				NL_SET_ERR_MSG_MOD(extack, "Setup for XDP failed");
				goto err;
			}
		}

		if (!old_prog) {
			peer->hw_features &= ~NETIF_F_GSO_SOFTWARE;
			peer->max_mtu = max_mtu;
		}
	}

	if (old_prog) {
		if (!prog) {
			if (dev->flags & IFF_UP)
				veth_disable_xdp(dev);

			if (peer) {
				peer->hw_features |= NETIF_F_GSO_SOFTWARE;
				peer->max_mtu = ETH_MAX_MTU;
			}
		}
		bpf_prog_put(old_prog);
	}

	if ((!!old_prog ^ !!prog) && peer)
		netdev_update_features(peer);

	return 0;
err:
	priv->_xdp_prog = old_prog;

	return err;
}
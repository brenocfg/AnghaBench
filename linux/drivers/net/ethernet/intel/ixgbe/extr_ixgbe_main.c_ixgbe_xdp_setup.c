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
struct net_device {int mtu; } ;
struct ixgbe_ring {struct bpf_prog* xdp_prog; } ;
struct ixgbe_adapter {int flags; int num_rx_queues; int /*<<< orphan*/  netdev; TYPE_1__** xdp_ring; struct bpf_prog* xdp_prog; struct ixgbe_ring** rx_ring; int /*<<< orphan*/  hw_tcs; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {scalar_t__ xsk_umem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IXGBE_FLAG_DCB_ENABLED ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 scalar_t__ MAX_XDP_QUEUES ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  XDP_WAKEUP_RX ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int ixgbe_rx_bufsz (struct ixgbe_ring*) ; 
 int ixgbe_setup_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_xsk_wakeup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct bpf_prog*,struct bpf_prog*) ; 
 scalar_t__ ring_is_rsc_enabled (struct ixgbe_ring*) ; 
 struct bpf_prog* xchg (struct bpf_prog**,struct bpf_prog*) ; 

__attribute__((used)) static int ixgbe_xdp_setup(struct net_device *dev, struct bpf_prog *prog)
{
	int i, frame_size = dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct bpf_prog *old_prog;
	bool need_reset;

	if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		return -EINVAL;

	if (adapter->flags & IXGBE_FLAG_DCB_ENABLED)
		return -EINVAL;

	/* verify ixgbe ring attributes are sufficient for XDP */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct ixgbe_ring *ring = adapter->rx_ring[i];

		if (ring_is_rsc_enabled(ring))
			return -EINVAL;

		if (frame_size > ixgbe_rx_bufsz(ring))
			return -EINVAL;
	}

	if (nr_cpu_ids > MAX_XDP_QUEUES)
		return -ENOMEM;

	old_prog = xchg(&adapter->xdp_prog, prog);
	need_reset = (!!prog != !!old_prog);

	/* If transitioning XDP modes reconfigure rings */
	if (need_reset) {
		int err = ixgbe_setup_tc(dev, adapter->hw_tcs);

		if (err) {
			rcu_assign_pointer(adapter->xdp_prog, old_prog);
			return -EINVAL;
		}
	} else {
		for (i = 0; i < adapter->num_rx_queues; i++)
			(void)xchg(&adapter->rx_ring[i]->xdp_prog,
			    adapter->xdp_prog);
	}

	if (old_prog)
		bpf_prog_put(old_prog);

	/* Kick start the NAPI context if there is an AF_XDP socket open
	 * on that queue id. This so that receiving will start.
	 */
	if (need_reset && prog)
		for (i = 0; i < adapter->num_rx_queues; i++)
			if (adapter->xdp_ring[i]->xsk_umem)
				(void)ixgbe_xsk_wakeup(adapter->netdev, i,
						       XDP_WAKEUP_RX);

	return 0;
}
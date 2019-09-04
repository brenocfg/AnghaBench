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
struct net_device {int mtu; } ;
struct ixgbevf_ring {struct bpf_prog* xdp_prog; } ;
struct ixgbevf_adapter {int num_rx_queues; struct bpf_prog* xdp_prog; struct ixgbevf_ring** rx_ring; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  ixgbevf_clear_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_close (struct net_device*) ; 
 int /*<<< orphan*/  ixgbevf_init_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_open (struct net_device*) ; 
 int ixgbevf_rx_bufsz (struct ixgbevf_ring*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct bpf_prog* xchg (struct bpf_prog**,struct bpf_prog*) ; 

__attribute__((used)) static int ixgbevf_xdp_setup(struct net_device *dev, struct bpf_prog *prog)
{
	int i, frame_size = dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	struct ixgbevf_adapter *adapter = netdev_priv(dev);
	struct bpf_prog *old_prog;

	/* verify ixgbevf ring attributes are sufficient for XDP */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct ixgbevf_ring *ring = adapter->rx_ring[i];

		if (frame_size > ixgbevf_rx_bufsz(ring))
			return -EINVAL;
	}

	old_prog = xchg(&adapter->xdp_prog, prog);

	/* If transitioning XDP modes reconfigure rings */
	if (!!prog != !!old_prog) {
		/* Hardware has to reinitialize queues and interrupts to
		 * match packet buffer alignment. Unfortunately, the
		 * hardware is not flexible enough to do this dynamically.
		 */
		if (netif_running(dev))
			ixgbevf_close(dev);

		ixgbevf_clear_interrupt_scheme(adapter);
		ixgbevf_init_interrupt_scheme(adapter);

		if (netif_running(dev))
			ixgbevf_open(dev);
	} else {
		for (i = 0; i < adapter->num_rx_queues; i++)
			xchg(&adapter->rx_ring[i]->xdp_prog, adapter->xdp_prog);
	}

	if (old_prog)
		bpf_prog_put(old_prog);

	return 0;
}
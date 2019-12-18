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
struct nicvf {scalar_t__ rx_queues; scalar_t__ tx_queues; scalar_t__ max_queues; struct net_device* netdev; int /*<<< orphan*/ * xdp_prog; } ;
struct net_device {scalar_t__ mtu; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_XDP_MTU ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bpf_prog_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,scalar_t__) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_open (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_set_xdp_queues (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_stop (struct net_device*) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ **,struct bpf_prog*) ; 

__attribute__((used)) static int nicvf_xdp_setup(struct nicvf *nic, struct bpf_prog *prog)
{
	struct net_device *dev = nic->netdev;
	bool if_up = netif_running(nic->netdev);
	struct bpf_prog *old_prog;
	bool bpf_attached = false;
	int ret = 0;

	/* For now just support only the usual MTU sized frames,
	 * plus some headroom for VLAN, QinQ.
	 */
	if (prog && dev->mtu > MAX_XDP_MTU) {
		netdev_warn(dev, "Jumbo frames not yet supported with XDP, current MTU %d.\n",
			    dev->mtu);
		return -EOPNOTSUPP;
	}

	/* ALL SQs attached to CQs i.e same as RQs, are treated as
	 * XDP Tx queues and more Tx queues are allocated for
	 * network stack to send pkts out.
	 *
	 * No of Tx queues are either same as Rx queues or whatever
	 * is left in max no of queues possible.
	 */
	if ((nic->rx_queues + nic->tx_queues) > nic->max_queues) {
		netdev_warn(dev,
			    "Failed to attach BPF prog, RXQs + TXQs > Max %d\n",
			    nic->max_queues);
		return -ENOMEM;
	}

	if (if_up)
		nicvf_stop(nic->netdev);

	old_prog = xchg(&nic->xdp_prog, prog);
	/* Detach old prog, if any */
	if (old_prog)
		bpf_prog_put(old_prog);

	if (nic->xdp_prog) {
		/* Attach BPF program */
		nic->xdp_prog = bpf_prog_add(nic->xdp_prog, nic->rx_queues - 1);
		if (!IS_ERR(nic->xdp_prog)) {
			bpf_attached = true;
		} else {
			ret = PTR_ERR(nic->xdp_prog);
			nic->xdp_prog = NULL;
		}
	}

	/* Calculate Tx queues needed for XDP and network stack */
	nicvf_set_xdp_queues(nic, bpf_attached);

	if (if_up) {
		/* Reinitialize interface, clean slate */
		nicvf_open(nic->netdev);
		netif_trans_update(nic->netdev);
	}

	return ret;
}
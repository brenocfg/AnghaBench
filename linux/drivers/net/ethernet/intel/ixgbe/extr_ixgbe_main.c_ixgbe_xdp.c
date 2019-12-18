#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  umem; } ;
struct netdev_bpf {int command; TYPE_3__ xsk; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {TYPE_2__* xdp_prog; } ;
struct TYPE_5__ {TYPE_1__* aux; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_XSK_UMEM 128 
 int ixgbe_xdp_setup (struct net_device*,int /*<<< orphan*/ ) ; 
 int ixgbe_xsk_umem_setup (struct ixgbe_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_xdp(struct net_device *dev, struct netdev_bpf *xdp)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return ixgbe_xdp_setup(dev, xdp->prog);
	case XDP_QUERY_PROG:
		xdp->prog_id = adapter->xdp_prog ?
			adapter->xdp_prog->aux->id : 0;
		return 0;
	case XDP_SETUP_XSK_UMEM:
		return ixgbe_xsk_umem_setup(adapter, xdp->xsk.umem,
					    xdp->xsk.queue_id);

	default:
		return -EINVAL;
	}
}
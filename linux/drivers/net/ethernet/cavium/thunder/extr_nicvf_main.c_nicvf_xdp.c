#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nicvf {TYPE_2__* xdp_prog; int /*<<< orphan*/  pdev; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int nicvf_xdp_setup (struct nicvf*,int /*<<< orphan*/ ) ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nicvf_xdp(struct net_device *netdev, struct netdev_bpf *xdp)
{
	struct nicvf *nic = netdev_priv(netdev);

	/* To avoid checks while retrieving buffer address from CQE_RX,
	 * do not support XDP for T88 pass1.x silicons which are anyway
	 * not in use widely.
	 */
	if (pass1_silicon(nic->pdev))
		return -EOPNOTSUPP;

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return nicvf_xdp_setup(nic, xdp->prog);
	case XDP_QUERY_PROG:
		xdp->prog_id = nic->xdp_prog ? nic->xdp_prog->aux->id : 0;
		return 0;
	default:
		return -EINVAL;
	}
}
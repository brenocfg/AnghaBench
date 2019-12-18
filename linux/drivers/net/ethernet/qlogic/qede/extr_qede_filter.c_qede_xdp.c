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
struct qede_dev {TYPE_2__* xdp_prog; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int qede_xdp_set (struct qede_dev*,int /*<<< orphan*/ ) ; 

int qede_xdp(struct net_device *dev, struct netdev_bpf *xdp)
{
	struct qede_dev *edev = netdev_priv(dev);

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return qede_xdp_set(edev, xdp->prog);
	case XDP_QUERY_PROG:
		xdp->prog_id = edev->xdp_prog ? edev->xdp_prog->aux->id : 0;
		return 0;
	default:
		return -EINVAL;
	}
}
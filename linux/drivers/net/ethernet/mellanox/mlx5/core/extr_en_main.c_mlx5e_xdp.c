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
struct TYPE_2__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  umem; } ;
struct netdev_bpf {int command; TYPE_1__ xsk; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_XSK_UMEM 128 
 int /*<<< orphan*/  mlx5e_xdp_query (struct net_device*) ; 
 int mlx5e_xdp_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int mlx5e_xsk_setup_umem (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_xdp(struct net_device *dev, struct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return mlx5e_xdp_set(dev, xdp->prog);
	case XDP_QUERY_PROG:
		xdp->prog_id = mlx5e_xdp_query(dev);
		return 0;
	case XDP_SETUP_XSK_UMEM:
		return mlx5e_xsk_setup_umem(dev, xdp->xsk.umem,
					    xdp->xsk.queue_id);
	default:
		return -EINVAL;
	}
}
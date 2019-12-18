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
struct netdevsim {int /*<<< orphan*/  bpf_map_accept; int /*<<< orphan*/  xdp_hw; int /*<<< orphan*/  xdp; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  offmap; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
#define  BPF_OFFLOAD_MAP_ALLOC 133 
#define  BPF_OFFLOAD_MAP_FREE 132 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  XDP_QUERY_PROG 131 
#define  XDP_QUERY_PROG_HW 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_PROG_HW 128 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int nsim_bpf_map_alloc (struct netdevsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_bpf_map_free (int /*<<< orphan*/ ) ; 
 int nsim_setup_prog_checks (struct netdevsim*,struct netdev_bpf*) ; 
 int nsim_setup_prog_hw_checks (struct netdevsim*,struct netdev_bpf*) ; 
 int nsim_xdp_set_prog (struct netdevsim*,struct netdev_bpf*,int /*<<< orphan*/ *) ; 
 int xdp_attachment_query (int /*<<< orphan*/ *,struct netdev_bpf*) ; 

int nsim_bpf(struct net_device *dev, struct netdev_bpf *bpf)
{
	struct netdevsim *ns = netdev_priv(dev);
	int err;

	ASSERT_RTNL();

	switch (bpf->command) {
	case XDP_QUERY_PROG:
		return xdp_attachment_query(&ns->xdp, bpf);
	case XDP_QUERY_PROG_HW:
		return xdp_attachment_query(&ns->xdp_hw, bpf);
	case XDP_SETUP_PROG:
		err = nsim_setup_prog_checks(ns, bpf);
		if (err)
			return err;

		return nsim_xdp_set_prog(ns, bpf, &ns->xdp);
	case XDP_SETUP_PROG_HW:
		err = nsim_setup_prog_hw_checks(ns, bpf);
		if (err)
			return err;

		return nsim_xdp_set_prog(ns, bpf, &ns->xdp_hw);
	case BPF_OFFLOAD_MAP_ALLOC:
		if (!ns->bpf_map_accept)
			return -EOPNOTSUPP;

		return nsim_bpf_map_alloc(ns, bpf->offmap);
	case BPF_OFFLOAD_MAP_FREE:
		nsim_bpf_map_free(bpf->offmap);
		return 0;
	default:
		return -EINVAL;
	}
}
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
struct nfp_net {int /*<<< orphan*/  app; int /*<<< orphan*/  xdp_hw; int /*<<< orphan*/  xdp; } ;
struct netdev_bpf {int command; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  XDP_QUERY_PROG 131 
#define  XDP_QUERY_PROG_HW 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_PROG_HW 128 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int nfp_app_bpf (int /*<<< orphan*/ ,struct nfp_net*,struct netdev_bpf*) ; 
 int nfp_net_xdp_setup_drv (struct nfp_net*,struct netdev_bpf*) ; 
 int nfp_net_xdp_setup_hw (struct nfp_net*,struct netdev_bpf*) ; 
 int xdp_attachment_query (int /*<<< orphan*/ *,struct netdev_bpf*) ; 

__attribute__((used)) static int nfp_net_xdp(struct net_device *netdev, struct netdev_bpf *xdp)
{
	struct nfp_net *nn = netdev_priv(netdev);

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return nfp_net_xdp_setup_drv(nn, xdp);
	case XDP_SETUP_PROG_HW:
		return nfp_net_xdp_setup_hw(nn, xdp);
	case XDP_QUERY_PROG:
		return xdp_attachment_query(&nn->xdp, xdp);
	case XDP_QUERY_PROG_HW:
		return xdp_attachment_query(&nn->xdp_hw, xdp);
	default:
		return nfp_app_bpf(nn->app, nn, xdp);
	}
}
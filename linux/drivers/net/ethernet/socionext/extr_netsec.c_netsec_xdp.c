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
struct netsec_priv {TYPE_2__* xdp_prog; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  extack; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int netsec_xdp_setup (struct netsec_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netsec_xdp(struct net_device *ndev, struct netdev_bpf *xdp)
{
	struct netsec_priv *priv = netdev_priv(ndev);

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return netsec_xdp_setup(priv, xdp->prog, xdp->extack);
	case XDP_QUERY_PROG:
		xdp->prog_id = priv->xdp_prog ? priv->xdp_prog->aux->id : 0;
		return 0;
	default:
		return -EINVAL;
	}
}
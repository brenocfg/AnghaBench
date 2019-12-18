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
struct TYPE_5__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  umem; } ;
struct netdev_bpf {int command; TYPE_2__ xsk; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;
struct i40e_vsi {scalar_t__ type; TYPE_3__* xdp_prog; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct TYPE_6__ {TYPE_1__* aux; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I40E_VSI_MAIN ; 
#define  XDP_QUERY_PROG 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_XSK_UMEM 128 
 int i40e_xdp_setup (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int i40e_xsk_umem_setup (struct i40e_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_xdp(struct net_device *dev,
		    struct netdev_bpf *xdp)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	struct i40e_vsi *vsi = np->vsi;

	if (vsi->type != I40E_VSI_MAIN)
		return -EINVAL;

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return i40e_xdp_setup(vsi, xdp->prog);
	case XDP_QUERY_PROG:
		xdp->prog_id = vsi->xdp_prog ? vsi->xdp_prog->aux->id : 0;
		return 0;
	case XDP_SETUP_XSK_UMEM:
		return i40e_xsk_umem_setup(vsi, xdp->xsk.umem,
					   xdp->xsk.queue_id);
	default:
		return -EINVAL;
	}
}
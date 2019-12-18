#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfp_reprs {int /*<<< orphan*/ * reprs; } ;
struct nfp_repr {struct nfp_abm_link* app_priv; } ;
struct nfp_port {int eth_forced; int pf_split; size_t pf_split_id; int /*<<< orphan*/  vnic; int /*<<< orphan*/  pf_id; } ;
struct nfp_app {int /*<<< orphan*/  cpp; TYPE_5__* pf; } ;
struct nfp_abm_link {size_t id; TYPE_4__* vnic; TYPE_1__* abm; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;
typedef  enum nfp_port_type { ____Placeholder_nfp_port_type } nfp_port_type ;
struct TYPE_10__ {int max_data_vnics; } ;
struct TYPE_8__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  ctrl_bar; } ;
struct TYPE_9__ {unsigned int max_rx_rings; TYPE_3__ dp; TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pf_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct nfp_port*) ; 
 int NFP_PORT_PF_PORT ; 
 int NFP_PORT_PHYS_PORT ; 
 int NFP_REPR_TYPE_PF ; 
 int NFP_REPR_TYPE_PHYS_PORT ; 
 int PTR_ERR (struct nfp_port*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_abm_portid (int,size_t) ; 
 int /*<<< orphan*/  nfp_info (int /*<<< orphan*/ ,char*,char*,size_t,int /*<<< orphan*/ ) ; 
 struct nfp_port* nfp_port_alloc (struct nfp_app*,int,struct net_device*) ; 
 int /*<<< orphan*/  nfp_port_free (struct nfp_port*) ; 
 int nfp_port_init_phy_port (TYPE_5__*,struct nfp_app*,struct nfp_port*,size_t) ; 
 struct net_device* nfp_repr_alloc_mqs (struct nfp_app*,unsigned int,int) ; 
 int /*<<< orphan*/  nfp_repr_free (struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_get_locked (struct nfp_app*,struct nfp_reprs*,size_t) ; 
 int nfp_repr_init (struct nfp_app*,struct net_device*,int /*<<< orphan*/ ,struct nfp_port*,int /*<<< orphan*/ ) ; 
 struct nfp_reprs* nfp_reprs_get_locked (struct nfp_app*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int
nfp_abm_spawn_repr(struct nfp_app *app, struct nfp_abm_link *alink,
		   enum nfp_port_type ptype)
{
	struct net_device *netdev;
	enum nfp_repr_type rtype;
	struct nfp_reprs *reprs;
	struct nfp_repr *repr;
	struct nfp_port *port;
	unsigned int txqs;
	int err;

	if (ptype == NFP_PORT_PHYS_PORT) {
		rtype = NFP_REPR_TYPE_PHYS_PORT;
		txqs = 1;
	} else {
		rtype = NFP_REPR_TYPE_PF;
		txqs = alink->vnic->max_rx_rings;
	}

	netdev = nfp_repr_alloc_mqs(app, txqs, 1);
	if (!netdev)
		return -ENOMEM;
	repr = netdev_priv(netdev);
	repr->app_priv = alink;

	port = nfp_port_alloc(app, ptype, netdev);
	if (IS_ERR(port)) {
		err = PTR_ERR(port);
		goto err_free_repr;
	}

	if (ptype == NFP_PORT_PHYS_PORT) {
		port->eth_forced = true;
		err = nfp_port_init_phy_port(app->pf, app, port, alink->id);
		if (err)
			goto err_free_port;
	} else {
		port->pf_id = alink->abm->pf_id;
		port->pf_split = app->pf->max_data_vnics > 1;
		port->pf_split_id = alink->id;
		port->vnic = alink->vnic->dp.ctrl_bar;
	}

	SET_NETDEV_DEV(netdev, &alink->vnic->pdev->dev);
	eth_hw_addr_random(netdev);

	err = nfp_repr_init(app, netdev, nfp_abm_portid(rtype, alink->id),
			    port, alink->vnic->dp.netdev);
	if (err)
		goto err_free_port;

	reprs = nfp_reprs_get_locked(app, rtype);
	WARN(nfp_repr_get_locked(app, reprs, alink->id), "duplicate repr");
	rtnl_lock();
	rcu_assign_pointer(reprs->reprs[alink->id], netdev);
	rtnl_unlock();

	nfp_info(app->cpp, "%s Port %d Representor(%s) created\n",
		 ptype == NFP_PORT_PF_PORT ? "PCIe" : "Phys",
		 alink->id, netdev->name);

	return 0;

err_free_port:
	nfp_port_free(port);
err_free_repr:
	nfp_repr_free(netdev);
	return err;
}
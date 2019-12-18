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
struct net_device {int flags; int /*<<< orphan*/  mc; } ;
struct cpsw_priv {int emac_port; struct cpsw_common* cpsw; } ;
struct TYPE_2__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  ale; TYPE_1__ data; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __hw_addr_ref_sync_dev (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_add_mc_addr ; 
 int /*<<< orphan*/  cpsw_ale_set_allmulti (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpsw_del_mc_addr ; 
 int /*<<< orphan*/  cpsw_set_promiscious (struct net_device*,int) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cpsw_ndo_set_rx_mode(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int slave_port = -1;

	if (cpsw->data.dual_emac)
		slave_port = priv->emac_port + 1;

	if (ndev->flags & IFF_PROMISC) {
		/* Enable promiscuous mode */
		cpsw_set_promiscious(ndev, true);
		cpsw_ale_set_allmulti(cpsw->ale, IFF_ALLMULTI, slave_port);
		return;
	} else {
		/* Disable promiscuous mode */
		cpsw_set_promiscious(ndev, false);
	}

	/* Restore allmulti on vlans if necessary */
	cpsw_ale_set_allmulti(cpsw->ale,
			      ndev->flags & IFF_ALLMULTI, slave_port);

	/* add/remove mcast address either for real netdev or for vlan */
	__hw_addr_ref_sync_dev(&ndev->mc, ndev, cpsw_add_mc_addr,
			       cpsw_del_mc_addr);
}
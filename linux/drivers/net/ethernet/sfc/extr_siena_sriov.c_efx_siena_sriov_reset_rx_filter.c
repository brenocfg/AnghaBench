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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  tci; } ;
struct siena_vf {int rx_filter_id; int /*<<< orphan*/  pci_name; TYPE_1__ addr; int /*<<< orphan*/  rx_filter_qid; int /*<<< orphan*/  rx_filter_flags; int /*<<< orphan*/  rx_filtering; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_filter_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_FILTER_PRI_REQUIRED ; 
 int EFX_FILTER_VID_UNSPEC ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  abs_index (struct siena_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_filter_init_rx (struct efx_filter_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_filter_insert_filter (struct efx_nic*,struct efx_filter_spec*,int) ; 
 int /*<<< orphan*/  efx_filter_remove_id_safe (struct efx_nic*,int /*<<< orphan*/ ,int) ; 
 int efx_filter_set_eth_local (struct efx_filter_spec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_siena_sriov_reset_rx_filter(struct siena_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	struct efx_filter_spec filter;
	u16 vlan;
	int rc;

	if (vf->rx_filter_id != -1) {
		efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  vf->rx_filter_id);
		netif_dbg(efx, hw, efx->net_dev, "Removed vf %s rx filter %d\n",
			  vf->pci_name, vf->rx_filter_id);
		vf->rx_filter_id = -1;
	}

	if (!vf->rx_filtering || is_zero_ether_addr(vf->addr.mac_addr))
		return;

	vlan = ntohs(vf->addr.tci) & VLAN_VID_MASK;
	efx_filter_init_rx(&filter, EFX_FILTER_PRI_REQUIRED,
			   vf->rx_filter_flags,
			   abs_index(vf, vf->rx_filter_qid));
	rc = efx_filter_set_eth_local(&filter,
				      vlan ? vlan : EFX_FILTER_VID_UNSPEC,
				      vf->addr.mac_addr);
	BUG_ON(rc);

	rc = efx_filter_insert_filter(efx, &filter, true);
	if (rc < 0) {
		netif_warn(efx, hw, efx->net_dev,
			   "Unable to insert rx filter for vf %s\n",
			   vf->pci_name);
	} else {
		netif_dbg(efx, hw, efx->net_dev, "Inserted vf %s rx filter %d\n",
			  vf->pci_name, rc);
		vf->rx_filter_id = rc;
	}
}
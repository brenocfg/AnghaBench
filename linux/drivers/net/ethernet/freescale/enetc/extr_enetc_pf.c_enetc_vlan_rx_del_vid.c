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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct enetc_pf {int /*<<< orphan*/  active_vlans; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  si; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_enable_si_vlan_promisc (struct enetc_pf*,int /*<<< orphan*/ ) ; 
 struct enetc_pf* enetc_si_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_sync_vlan_ht_filter (struct enetc_pf*,int) ; 
 int /*<<< orphan*/  enetc_vlan_filter_is_on (struct enetc_pf*) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_vlan_rx_del_vid(struct net_device *ndev, __be16 prot, u16 vid)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_pf *pf = enetc_si_priv(priv->si);

	__clear_bit(vid, pf->active_vlans);
	enetc_sync_vlan_ht_filter(pf, true);

	if (!enetc_vlan_filter_is_on(pf))
		enetc_enable_si_vlan_promisc(pf, 0);

	return 0;
}
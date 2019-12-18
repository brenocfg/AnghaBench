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
struct enetc_pf {int /*<<< orphan*/  vlan_ht_filter; int /*<<< orphan*/  active_vlans; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  si; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_disable_si_vlan_promisc (struct enetc_pf*,int /*<<< orphan*/ ) ; 
 struct enetc_pf* enetc_si_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ enetc_si_vlan_promisc_is_on (struct enetc_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_sync_vlan_ht_filter (struct enetc_pf*,int) ; 
 int enetc_vid_hash_idx (int /*<<< orphan*/ ) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_vlan_rx_add_vid(struct net_device *ndev, __be16 prot, u16 vid)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_pf *pf = enetc_si_priv(priv->si);
	int idx;

	if (enetc_si_vlan_promisc_is_on(pf, 0))
		enetc_disable_si_vlan_promisc(pf, 0);

	__set_bit(vid, pf->active_vlans);

	idx = enetc_vid_hash_idx(vid);
	if (!__test_and_set_bit(idx, pf->vlan_ht_filter))
		enetc_sync_vlan_ht_filter(pf, false);

	return 0;
}
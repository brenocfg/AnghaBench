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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct enetc_vf_state {int /*<<< orphan*/  flags; } ;
struct enetc_pf {int total_vfs; struct enetc_vf_state* vf_state; } ;
struct enetc_ndev_priv {TYPE_1__* si; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENETC_VF_FLAG_PF_SET_MAC ; 
 int /*<<< orphan*/  enetc_pf_set_primary_mac_addr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct enetc_pf* enetc_si_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_pf_set_vf_mac(struct net_device *ndev, int vf, u8 *mac)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_pf *pf = enetc_si_priv(priv->si);
	struct enetc_vf_state *vf_state;

	if (vf >= pf->total_vfs)
		return -EINVAL;

	if (!is_valid_ether_addr(mac))
		return -EADDRNOTAVAIL;

	vf_state = &pf->vf_state[vf];
	vf_state->flags |= ENETC_VF_FLAG_PF_SET_MAC;
	enetc_pf_set_primary_mac_addr(&priv->si->hw, vf + 1, mac);
	return 0;
}
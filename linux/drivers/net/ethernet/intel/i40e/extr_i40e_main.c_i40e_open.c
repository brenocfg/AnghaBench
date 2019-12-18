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
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  I40E_GLLAN_TSOMSK_F ; 
 int /*<<< orphan*/  I40E_GLLAN_TSOMSK_L ; 
 int /*<<< orphan*/  I40E_GLLAN_TSOMSK_M ; 
 int TCP_FLAG_CWR ; 
 int TCP_FLAG_FIN ; 
 int TCP_FLAG_PSH ; 
 int /*<<< orphan*/  __I40E_BAD_EEPROM ; 
 int /*<<< orphan*/  __I40E_TESTING ; 
 int be32_to_cpu (int) ; 
 scalar_t__ i40e_force_link_state (struct i40e_pf*,int) ; 
 int i40e_vsi_open (struct i40e_vsi*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int i40e_open(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	int err;

	/* disallow open during test or if eeprom is broken */
	if (test_bit(__I40E_TESTING, pf->state) ||
	    test_bit(__I40E_BAD_EEPROM, pf->state))
		return -EBUSY;

	netif_carrier_off(netdev);

	if (i40e_force_link_state(pf, true))
		return -EAGAIN;

	err = i40e_vsi_open(vsi);
	if (err)
		return err;

	/* configure global TSO hardware offload settings */
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_F, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_M, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN |
						       TCP_FLAG_CWR) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_L, be32_to_cpu(TCP_FLAG_CWR) >> 16);

	udp_tunnel_get_rx_info(netdev);

	return 0;
}
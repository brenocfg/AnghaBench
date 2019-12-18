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
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_hw {int partition_id; int /*<<< orphan*/  port; } ;
struct i40e_pf {size_t lan_vsi; int wol_en; TYPE_1__* pdev; struct i40e_vsi** vsi; struct i40e_hw hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I40E_SR_NVM_WAKE_ON_LAN ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40e_partition_setting_complaint (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_read_nvm_word (struct i40e_hw*,int /*<<< orphan*/ ,int*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_hw *hw = &pf->hw;
	u16 wol_nvm_bits;

	/* WoL not supported if this isn't the controlling PF on the port */
	if (hw->partition_id != 1) {
		i40e_partition_setting_complaint(pf);
		return -EOPNOTSUPP;
	}

	if (vsi != pf->vsi[pf->lan_vsi])
		return -EOPNOTSUPP;

	/* NVM bit on means WoL disabled for the port */
	i40e_read_nvm_word(hw, I40E_SR_NVM_WAKE_ON_LAN, &wol_nvm_bits);
	if (BIT(hw->port) & wol_nvm_bits)
		return -EOPNOTSUPP;

	/* only magic packet is supported */
	if (wol->wolopts & ~WAKE_MAGIC)
		return -EOPNOTSUPP;

	/* is this a new value? */
	if (pf->wol_en != !!wol->wolopts) {
		pf->wol_en = !!wol->wolopts;
		device_set_wakeup_enable(&pf->pdev->dev, pf->wol_en);
	}

	return 0;
}
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
struct i40e_hw {int partition_id; int /*<<< orphan*/  port; } ;
struct i40e_pf {scalar_t__ wol_en; struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct ethtool_wolinfo {void* wolopts; void* supported; } ;
struct TYPE_2__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_SR_NVM_WAKE_ON_LAN ; 
 void* WAKE_MAGIC ; 
 int /*<<< orphan*/  i40e_read_nvm_word (struct i40e_hw*,int /*<<< orphan*/ ,int*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40e_get_wol(struct net_device *netdev,
			 struct ethtool_wolinfo *wol)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u16 wol_nvm_bits;

	/* NVM bit on means WoL disabled for the port */
	i40e_read_nvm_word(hw, I40E_SR_NVM_WAKE_ON_LAN, &wol_nvm_bits);
	if ((BIT(hw->port) & wol_nvm_bits) || (hw->partition_id != 1)) {
		wol->supported = 0;
		wol->wolopts = 0;
	} else {
		wol->supported = WAKE_MAGIC;
		wol->wolopts = (pf->wol_en ? WAKE_MAGIC : 0);
	}
}
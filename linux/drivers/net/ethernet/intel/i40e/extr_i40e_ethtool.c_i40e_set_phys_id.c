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
struct i40e_hw {int flags; } ;
struct i40e_pf {int hw_features; int led_status; int phy_led_val; struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
typedef  scalar_t__ i40e_status ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
struct TYPE_2__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int ENOENT ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE ; 
 int I40E_HW_PHY_CONTROLS_LEDS ; 
 int /*<<< orphan*/  I40E_PHY_DEBUG_ALL ; 
 int I40E_PHY_LED_MODE_ORIG ; 
 int /*<<< orphan*/  i40e_aq_set_phy_debug (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i40e_led_get (struct i40e_hw*) ; 
 scalar_t__ i40e_led_get_phy (struct i40e_hw*,int*,int*) ; 
 int /*<<< orphan*/  i40e_led_set (struct i40e_hw*,int,int) ; 
 scalar_t__ i40e_led_set_phy (struct i40e_hw*,int,int,int) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_set_phys_id(struct net_device *netdev,
			    enum ethtool_phys_id_state state)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	i40e_status ret = 0;
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	int blink_freq = 2;
	u16 temp_status;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		if (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS)) {
			pf->led_status = i40e_led_get(hw);
		} else {
			if (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE))
				i40e_aq_set_phy_debug(hw, I40E_PHY_DEBUG_ALL,
						      NULL);
			ret = i40e_led_get_phy(hw, &temp_status,
					       &pf->phy_led_val);
			pf->led_status = temp_status;
		}
		return blink_freq;
	case ETHTOOL_ID_ON:
		if (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS))
			i40e_led_set(hw, 0xf, false);
		else
			ret = i40e_led_set_phy(hw, true, pf->led_status, 0);
		break;
	case ETHTOOL_ID_OFF:
		if (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS))
			i40e_led_set(hw, 0x0, false);
		else
			ret = i40e_led_set_phy(hw, false, pf->led_status, 0);
		break;
	case ETHTOOL_ID_INACTIVE:
		if (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS)) {
			i40e_led_set(hw, pf->led_status, false);
		} else {
			ret = i40e_led_set_phy(hw, false, pf->led_status,
					       (pf->phy_led_val |
					       I40E_PHY_LED_MODE_ORIG));
			if (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE))
				i40e_aq_set_phy_debug(hw, 0, NULL);
		}
		break;
	default:
		break;
	}
	if (ret)
		return -ENOENT;
	else
		return 0;
}
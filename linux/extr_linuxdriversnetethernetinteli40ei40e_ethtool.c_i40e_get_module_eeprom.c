#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_3__ {scalar_t__* module_type; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct i40e_hw {TYPE_2__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_eeprom {int len; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ ETH_MODULE_SFF_8079_LEN ; 
 scalar_t__ ETH_MODULE_SFF_8436_LEN ; 
 int /*<<< orphan*/  I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE ; 
 scalar_t__ I40E_I2C_EEPROM_DEV_ADDR ; 
 scalar_t__ I40E_I2C_EEPROM_DEV_ADDR2 ; 
 scalar_t__ I40E_MODULE_TYPE_SFP ; 
 int /*<<< orphan*/  i40e_aq_get_phy_register (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_module_eeprom(struct net_device *netdev,
				  struct ethtool_eeprom *ee,
				  u8 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	bool is_sfp = false;
	i40e_status status;
	u32 value = 0;
	int i;

	if (!ee || !ee->len || !data)
		return -EINVAL;

	if (hw->phy.link_info.module_type[0] == I40E_MODULE_TYPE_SFP)
		is_sfp = true;

	for (i = 0; i < ee->len; i++) {
		u32 offset = i + ee->offset;
		u32 addr = is_sfp ? I40E_I2C_EEPROM_DEV_ADDR : 0;

		/* Check if we need to access the other memory page */
		if (is_sfp) {
			if (offset >= ETH_MODULE_SFF_8079_LEN) {
				offset -= ETH_MODULE_SFF_8079_LEN;
				addr = I40E_I2C_EEPROM_DEV_ADDR2;
			}
		} else {
			while (offset >= ETH_MODULE_SFF_8436_LEN) {
				/* Compute memory page number and offset. */
				offset -= ETH_MODULE_SFF_8436_LEN / 2;
				addr++;
			}
		}

		status = i40e_aq_get_phy_register(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				addr, offset, &value, NULL);
		if (status)
			return -EIO;
		data[i] = value;
	}
	return 0;
}
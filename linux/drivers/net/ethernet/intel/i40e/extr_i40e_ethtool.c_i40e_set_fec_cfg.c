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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_2__ aq; } ;
struct i40e_pf {int /*<<< orphan*/  flags; struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct i40e_aq_set_phy_config {int fec_cfg_curr_mod_ext_info; int fec_config; int /*<<< orphan*/  d3_lpan; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  eeer_val; int /*<<< orphan*/  eeer; int /*<<< orphan*/  eee_capability; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  phy_type_ext; int /*<<< orphan*/  abilities; int /*<<< orphan*/  phy_type; } ;
struct i40e_aq_get_phy_abilities_resp {int fec_cfg_curr_mod_ext_info; int fec_config; int /*<<< orphan*/  d3_lpan; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  eeer_val; int /*<<< orphan*/  eeer; int /*<<< orphan*/  eee_capability; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  phy_type_ext; int /*<<< orphan*/  abilities; int /*<<< orphan*/  phy_type; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  config ;
typedef  int /*<<< orphan*/  abilities ;
struct TYPE_3__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I40E_AQ_PHY_FEC_CONFIG_MASK ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_get_phy_capabilities (struct i40e_hw*,int,int,struct i40e_aq_set_phy_config*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_set_phy_config (struct i40e_hw*,struct i40e_aq_set_phy_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_set_fec_in_flags (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 scalar_t__ i40e_update_link_info (struct i40e_hw*) ; 
 int /*<<< orphan*/  memset (struct i40e_aq_set_phy_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_set_fec_cfg(struct net_device *netdev, u8 fec_cfg)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_aq_get_phy_abilities_resp abilities;
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	i40e_status status = 0;
	u32 flags = 0;
	int err = 0;

	flags = READ_ONCE(pf->flags);
	i40e_set_fec_in_flags(fec_cfg, &flags);

	/* Get the current phy config */
	memset(&abilities, 0, sizeof(abilities));
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      NULL);
	if (status) {
		err = -EAGAIN;
		goto done;
	}

	if (abilities.fec_cfg_curr_mod_ext_info != fec_cfg) {
		struct i40e_aq_set_phy_config config;

		memset(&config, 0, sizeof(config));
		config.phy_type = abilities.phy_type;
		config.abilities = abilities.abilities;
		config.phy_type_ext = abilities.phy_type_ext;
		config.link_speed = abilities.link_speed;
		config.eee_capability = abilities.eee_capability;
		config.eeer = abilities.eeer_val;
		config.low_power_ctrl = abilities.d3_lpan;
		config.fec_config = fec_cfg & I40E_AQ_PHY_FEC_CONFIG_MASK;
		status = i40e_aq_set_phy_config(hw, &config, NULL);
		if (status) {
			netdev_info(netdev,
				    "Set phy config failed, err %s aq_err %s\n",
				    i40e_stat_str(hw, status),
				    i40e_aq_str(hw, hw->aq.asq_last_status));
			err = -EAGAIN;
			goto done;
		}
		pf->flags = flags;
		status = i40e_update_link_info(hw);
		if (status)
			/* debug level message only due to relation to the link
			 * itself rather than to the FEC settings
			 * (e.g. no physical connection etc.)
			 */
			netdev_dbg(netdev,
				   "Updating link info failed with err %s aq_err %s\n",
				   i40e_stat_str(hw, status),
				   i40e_aq_str(hw, hw->aq.asq_last_status));
	}

done:
	return err;
}
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
typedef  void* u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_2__ aq; } ;
struct i40e_pf {struct i40e_hw hw; TYPE_1__* pdev; } ;
struct i40e_aq_set_phy_config {scalar_t__ link_speed; int fec_config; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  eeer; int /*<<< orphan*/  eee_capability; int /*<<< orphan*/  abilities; void* phy_type_ext; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  member_0; } ;
struct i40e_aq_get_phy_abilities_resp {scalar_t__ link_speed; scalar_t__ phy_type; int fec_cfg_curr_mod_ext_info; int /*<<< orphan*/  d3_lpan; int /*<<< orphan*/  eeer_val; int /*<<< orphan*/  eee_capability; int /*<<< orphan*/  abilities; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_AQ_PHY_FEC_CONFIG_MASK ; 
 int I40E_PHY_TYPES_BITMASK ; 
 scalar_t__ I40E_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_get_phy_capabilities (struct i40e_hw*,int,int,struct i40e_aq_get_phy_abilities_resp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_set_link_restart_an (struct i40e_hw*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_set_phy_config (struct i40e_hw*,struct i40e_aq_set_phy_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 scalar_t__ i40e_update_link_info (struct i40e_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static i40e_status i40e_force_link_state(struct i40e_pf *pf, bool is_up)
{
	struct i40e_aq_get_phy_abilities_resp abilities;
	struct i40e_aq_set_phy_config config = {0};
	struct i40e_hw *hw = &pf->hw;
	i40e_status err;
	u64 mask;
	u8 speed;

	/* Card might've been put in an unstable state by other drivers
	 * and applications, which causes incorrect speed values being
	 * set on startup. In order to clear speed registers, we call
	 * get_phy_capabilities twice, once to get initial state of
	 * available speeds, and once to get current PHY config.
	 */
	err = i40e_aq_get_phy_capabilities(hw, false, true, &abilities,
					   NULL);
	if (err) {
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		return err;
	}
	speed = abilities.link_speed;

	/* Get the current phy config */
	err = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					   NULL);
	if (err) {
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		return err;
	}

	/* If link needs to go up, but was not forced to go down,
	 * and its speed values are OK, no need for a flap
	 */
	if (is_up && abilities.phy_type != 0 && abilities.link_speed != 0)
		return I40E_SUCCESS;

	/* To force link we need to set bits for all supported PHY types,
	 * but there are now more than 32, so we need to split the bitmap
	 * across two fields.
	 */
	mask = I40E_PHY_TYPES_BITMASK;
	config.phy_type = is_up ? cpu_to_le32((u32)(mask & 0xffffffff)) : 0;
	config.phy_type_ext = is_up ? (u8)((mask >> 32) & 0xff) : 0;
	/* Copy the old settings, except of phy_type */
	config.abilities = abilities.abilities;
	if (abilities.link_speed != 0)
		config.link_speed = abilities.link_speed;
	else
		config.link_speed = speed;
	config.eee_capability = abilities.eee_capability;
	config.eeer = abilities.eeer_val;
	config.low_power_ctrl = abilities.d3_lpan;
	config.fec_config = abilities.fec_cfg_curr_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;
	err = i40e_aq_set_phy_config(hw, &config, NULL);

	if (err) {
		dev_err(&pf->pdev->dev,
			"set phy config ret =  %s last_status =  %s\n",
			i40e_stat_str(&pf->hw, err),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		return err;
	}

	/* Update the link info */
	err = i40e_update_link_info(hw);
	if (err) {
		/* Wait a little bit (on 40G cards it sometimes takes a really
		 * long time for link to come back from the atomic reset)
		 * and try once more
		 */
		msleep(1000);
		i40e_update_link_info(hw);
	}

	i40e_aq_set_link_restart_an(hw, true, NULL);

	return I40E_SUCCESS;
}
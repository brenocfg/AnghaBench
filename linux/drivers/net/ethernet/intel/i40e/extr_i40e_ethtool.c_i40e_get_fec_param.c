#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int fec_info; } ;
struct TYPE_6__ {TYPE_2__ link_info; } ;
struct i40e_hw {TYPE_3__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct i40e_aq_get_phy_abilities_resp {int fec_cfg_curr_mod_ext_info; } ;
struct ethtool_fecparam {int /*<<< orphan*/  active_fec; int /*<<< orphan*/  fec; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  abilities ;
struct TYPE_4__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ETHTOOL_FEC_AUTO ; 
 int /*<<< orphan*/  ETHTOOL_FEC_BASER ; 
 int /*<<< orphan*/  ETHTOOL_FEC_OFF ; 
 int /*<<< orphan*/  ETHTOOL_FEC_RS ; 
 int I40E_AQ_CONFIG_FEC_KR_ENA ; 
 int I40E_AQ_CONFIG_FEC_RS_ENA ; 
 int I40E_AQ_SET_FEC_ABILITY_KR ; 
 int I40E_AQ_SET_FEC_ABILITY_RS ; 
 int I40E_AQ_SET_FEC_AUTO ; 
 int I40E_AQ_SET_FEC_REQUEST_KR ; 
 int I40E_AQ_SET_FEC_REQUEST_RS ; 
 scalar_t__ i40e_aq_get_phy_capabilities (struct i40e_hw*,int,int,struct i40e_aq_get_phy_abilities_resp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i40e_aq_get_phy_abilities_resp*,int /*<<< orphan*/ ,int) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_fec_param(struct net_device *netdev,
			      struct ethtool_fecparam *fecparam)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_aq_get_phy_abilities_resp abilities;
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	i40e_status status = 0;
	int err = 0;

	/* Get the current phy config */
	memset(&abilities, 0, sizeof(abilities));
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      NULL);
	if (status) {
		err = -EAGAIN;
		goto done;
	}

	fecparam->fec = 0;
	if (abilities.fec_cfg_curr_mod_ext_info & I40E_AQ_SET_FEC_AUTO)
		fecparam->fec |= ETHTOOL_FEC_AUTO;
	if ((abilities.fec_cfg_curr_mod_ext_info &
	     I40E_AQ_SET_FEC_REQUEST_RS) ||
	    (abilities.fec_cfg_curr_mod_ext_info &
	     I40E_AQ_SET_FEC_ABILITY_RS))
		fecparam->fec |= ETHTOOL_FEC_RS;
	if ((abilities.fec_cfg_curr_mod_ext_info &
	     I40E_AQ_SET_FEC_REQUEST_KR) ||
	    (abilities.fec_cfg_curr_mod_ext_info & I40E_AQ_SET_FEC_ABILITY_KR))
		fecparam->fec |= ETHTOOL_FEC_BASER;
	if (abilities.fec_cfg_curr_mod_ext_info == 0)
		fecparam->fec |= ETHTOOL_FEC_OFF;

	if (hw->phy.link_info.fec_info & I40E_AQ_CONFIG_FEC_KR_ENA)
		fecparam->active_fec = ETHTOOL_FEC_BASER;
	else if (hw->phy.link_info.fec_info & I40E_AQ_CONFIG_FEC_RS_ENA)
		fecparam->active_fec = ETHTOOL_FEC_RS;
	else
		fecparam->active_fec = ETHTOOL_FEC_OFF;
done:
	return err;
}
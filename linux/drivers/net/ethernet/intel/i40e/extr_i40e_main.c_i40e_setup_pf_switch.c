#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  void* u16 ;
struct i40e_vsi {int dummy; } ;
struct TYPE_18__ {int an_info; } ;
struct TYPE_19__ {TYPE_5__ link_info; } ;
struct TYPE_14__ {scalar_t__ asq_last_status; } ;
struct TYPE_13__ {scalar_t__ pf_id; TYPE_6__ phy; TYPE_1__ aq; } ;
struct i40e_pf {int flags; size_t lan_vsi; size_t lan_veb; int fc_autoneg_status; TYPE_10__ hw; TYPE_4__* pdev; TYPE_7__** vsi; int /*<<< orphan*/  main_vsi_seid; void* mac_seid; TYPE_2__** veb; void* last_sw_conf_valid_flags; void* last_sw_conf_flags; } ;
struct TYPE_16__ {scalar_t__ enabled_tc; } ;
struct TYPE_20__ {int /*<<< orphan*/  seid; TYPE_3__ tc_config; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {void* seid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I40E_AQ_AN_COMPLETED ; 
 scalar_t__ I40E_AQ_RC_ESRCH ; 
 void* I40E_AQ_SET_SWITCH_CFG_PROMISC ; 
 int I40E_FLAG_RSS_ENABLED ; 
 int I40E_FLAG_TRUE_PROMISC_SUPPORT ; 
 size_t I40E_MAX_VEB ; 
 size_t I40E_NO_VSI ; 
 int /*<<< orphan*/  I40E_VSI_MAIN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int i40e_aq_set_switch_config (TYPE_10__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (TYPE_10__*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_cloud_filter_exit (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_fdir_sb_setup (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_fdir_teardown (struct i40e_pf*) ; 
 int i40e_fetch_switch_configuration (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  i40e_link_event (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_pf_config_rss (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_pf_reset_stats (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_ptp_init (struct i40e_pf*) ; 
 int i40e_setup_pf_filter_control (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_stat_str (TYPE_10__*,int) ; 
 int /*<<< orphan*/  i40e_sync_udp_filters (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_vlan_stripping_disable (TYPE_7__*) ; 
 int /*<<< orphan*/  i40e_vsi_config_tc (TYPE_7__*,scalar_t__) ; 
 struct i40e_vsi* i40e_vsi_reinit_setup (TYPE_7__*) ; 
 struct i40e_vsi* i40e_vsi_setup (struct i40e_pf*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_setup_pf_switch(struct i40e_pf *pf, bool reinit)
{
	u16 flags = 0;
	int ret;

	/* find out what's out there already */
	ret = i40e_fetch_switch_configuration(pf, false);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "couldn't fetch switch config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		return ret;
	}
	i40e_pf_reset_stats(pf);

	/* set the switch config bit for the whole device to
	 * support limited promisc or true promisc
	 * when user requests promisc. The default is limited
	 * promisc.
	*/

	if ((pf->hw.pf_id == 0) &&
	    !(pf->flags & I40E_FLAG_TRUE_PROMISC_SUPPORT)) {
		flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		pf->last_sw_conf_flags = flags;
	}

	if (pf->hw.pf_id == 0) {
		u16 valid_flags;

		valid_flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		ret = i40e_aq_set_switch_config(&pf->hw, flags, valid_flags, 0,
						NULL);
		if (ret && pf->hw.aq.asq_last_status != I40E_AQ_RC_ESRCH) {
			dev_info(&pf->pdev->dev,
				 "couldn't set switch config bits, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			/* not a fatal problem, just keep going */
		}
		pf->last_sw_conf_valid_flags = valid_flags;
	}

	/* first time setup */
	if (pf->lan_vsi == I40E_NO_VSI || reinit) {
		struct i40e_vsi *vsi = NULL;
		u16 uplink_seid;

		/* Set up the PF VSI associated with the PF's main VSI
		 * that is already in the HW switch
		 */
		if (pf->lan_veb < I40E_MAX_VEB && pf->veb[pf->lan_veb])
			uplink_seid = pf->veb[pf->lan_veb]->seid;
		else
			uplink_seid = pf->mac_seid;
		if (pf->lan_vsi == I40E_NO_VSI)
			vsi = i40e_vsi_setup(pf, I40E_VSI_MAIN, uplink_seid, 0);
		else if (reinit)
			vsi = i40e_vsi_reinit_setup(pf->vsi[pf->lan_vsi]);
		if (!vsi) {
			dev_info(&pf->pdev->dev, "setup of MAIN VSI failed\n");
			i40e_cloud_filter_exit(pf);
			i40e_fdir_teardown(pf);
			return -EAGAIN;
		}
	} else {
		/* force a reset of TC and queue layout configurations */
		u8 enabled_tc = pf->vsi[pf->lan_vsi]->tc_config.enabled_tc;

		pf->vsi[pf->lan_vsi]->tc_config.enabled_tc = 0;
		pf->vsi[pf->lan_vsi]->seid = pf->main_vsi_seid;
		i40e_vsi_config_tc(pf->vsi[pf->lan_vsi], enabled_tc);
	}
	i40e_vlan_stripping_disable(pf->vsi[pf->lan_vsi]);

	i40e_fdir_sb_setup(pf);

	/* Setup static PF queue filter control settings */
	ret = i40e_setup_pf_filter_control(pf);
	if (ret) {
		dev_info(&pf->pdev->dev, "setup_pf_filter_control failed: %d\n",
			 ret);
		/* Failure here should not stop continuing other steps */
	}

	/* enable RSS in the HW, even for only one queue, as the stack can use
	 * the hash
	 */
	if ((pf->flags & I40E_FLAG_RSS_ENABLED))
		i40e_pf_config_rss(pf);

	/* fill in link information and enable LSE reporting */
	i40e_link_event(pf);

	/* Initialize user-specific link properties */
	pf->fc_autoneg_status = ((pf->hw.phy.link_info.an_info &
				  I40E_AQ_AN_COMPLETED) ? true : false);

	i40e_ptp_init(pf);

	/* repopulate tunnel port filters */
	i40e_sync_udp_filters(pf);

	return ret;
}
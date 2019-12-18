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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_link_status {int link_speed; int link_info; int an_info; int ext_info; int max_frame_size; int fec_info; int pacing; int lse_ena; void* phy_type_high; void* phy_type_low; int /*<<< orphan*/  topo_media_conflict; } ;
struct TYPE_4__ {int media_type; int get_link_info; struct ice_link_status link_info; struct ice_link_status link_info_old; } ;
struct ice_fc_info {int /*<<< orphan*/  current_mode; } ;
struct ice_port_info {TYPE_2__ phy; int /*<<< orphan*/  lport; struct ice_fc_info fc; struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_get_link_status_data {int link_info; int an_info; int ext_info; int cfg; int /*<<< orphan*/  topo_media_conflict; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  phy_type_high; int /*<<< orphan*/  phy_type_low; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  member_0; } ;
struct ice_aqc_get_link_status {int cmd_flags; int /*<<< orphan*/  lport_num; } ;
struct TYPE_3__ {struct ice_aqc_get_link_status get_link_status; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  link_data ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_media_type { ____Placeholder_ice_media_type } ice_media_type ;

/* Variables and functions */
 int ICE_AQ_CFG_PACING_M ; 
 int ICE_AQ_CFG_PACING_TYPE_M ; 
 int ICE_AQ_FEC_MASK ; 
 int ICE_AQ_LINK_PAUSE_RX ; 
 int ICE_AQ_LINK_PAUSE_TX ; 
 int /*<<< orphan*/  ICE_AQ_LSE_DIS ; 
 int /*<<< orphan*/  ICE_AQ_LSE_ENA ; 
 int /*<<< orphan*/  ICE_AQ_LSE_IS_ENABLED ; 
 int /*<<< orphan*/  ICE_DBG_LINK ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_FC_FULL ; 
 int /*<<< orphan*/  ICE_FC_NONE ; 
 int /*<<< orphan*/  ICE_FC_RX_PAUSE ; 
 int /*<<< orphan*/  ICE_FC_TX_PAUSE ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_get_link_status_data*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_get_link_status ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int ice_get_media_type (struct ice_port_info*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

enum ice_status
ice_aq_get_link_info(struct ice_port_info *pi, bool ena_lse,
		     struct ice_link_status *link, struct ice_sq_cd *cd)
{
	struct ice_aqc_get_link_status_data link_data = { 0 };
	struct ice_aqc_get_link_status *resp;
	struct ice_link_status *li_old, *li;
	enum ice_media_type *hw_media_type;
	struct ice_fc_info *hw_fc_info;
	bool tx_pause, rx_pause;
	struct ice_aq_desc desc;
	enum ice_status status;
	struct ice_hw *hw;
	u16 cmd_flags;

	if (!pi)
		return ICE_ERR_PARAM;
	hw = pi->hw;
	li_old = &pi->phy.link_info_old;
	hw_media_type = &pi->phy.media_type;
	li = &pi->phy.link_info;
	hw_fc_info = &pi->fc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_link_status);
	cmd_flags = (ena_lse) ? ICE_AQ_LSE_ENA : ICE_AQ_LSE_DIS;
	resp = &desc.params.get_link_status;
	resp->cmd_flags = cpu_to_le16(cmd_flags);
	resp->lport_num = pi->lport;

	status = ice_aq_send_cmd(hw, &desc, &link_data, sizeof(link_data), cd);

	if (status)
		return status;

	/* save off old link status information */
	*li_old = *li;

	/* update current link status information */
	li->link_speed = le16_to_cpu(link_data.link_speed);
	li->phy_type_low = le64_to_cpu(link_data.phy_type_low);
	li->phy_type_high = le64_to_cpu(link_data.phy_type_high);
	*hw_media_type = ice_get_media_type(pi);
	li->link_info = link_data.link_info;
	li->an_info = link_data.an_info;
	li->ext_info = link_data.ext_info;
	li->max_frame_size = le16_to_cpu(link_data.max_frame_size);
	li->fec_info = link_data.cfg & ICE_AQ_FEC_MASK;
	li->topo_media_conflict = link_data.topo_media_conflict;
	li->pacing = link_data.cfg & (ICE_AQ_CFG_PACING_M |
				      ICE_AQ_CFG_PACING_TYPE_M);

	/* update fc info */
	tx_pause = !!(link_data.an_info & ICE_AQ_LINK_PAUSE_TX);
	rx_pause = !!(link_data.an_info & ICE_AQ_LINK_PAUSE_RX);
	if (tx_pause && rx_pause)
		hw_fc_info->current_mode = ICE_FC_FULL;
	else if (tx_pause)
		hw_fc_info->current_mode = ICE_FC_TX_PAUSE;
	else if (rx_pause)
		hw_fc_info->current_mode = ICE_FC_RX_PAUSE;
	else
		hw_fc_info->current_mode = ICE_FC_NONE;

	li->lse_ena = !!(resp->cmd_flags & cpu_to_le16(ICE_AQ_LSE_IS_ENABLED));

	ice_debug(hw, ICE_DBG_LINK, "link_speed = 0x%x\n", li->link_speed);
	ice_debug(hw, ICE_DBG_LINK, "phy_type_low = 0x%llx\n",
		  (unsigned long long)li->phy_type_low);
	ice_debug(hw, ICE_DBG_LINK, "phy_type_high = 0x%llx\n",
		  (unsigned long long)li->phy_type_high);
	ice_debug(hw, ICE_DBG_LINK, "media_type = 0x%x\n", *hw_media_type);
	ice_debug(hw, ICE_DBG_LINK, "link_info = 0x%x\n", li->link_info);
	ice_debug(hw, ICE_DBG_LINK, "an_info = 0x%x\n", li->an_info);
	ice_debug(hw, ICE_DBG_LINK, "ext_info = 0x%x\n", li->ext_info);
	ice_debug(hw, ICE_DBG_LINK, "lse_ena = 0x%x\n", li->lse_ena);
	ice_debug(hw, ICE_DBG_LINK, "max_frame = 0x%x\n", li->max_frame_size);
	ice_debug(hw, ICE_DBG_LINK, "pacing = 0x%x\n", li->pacing);

	/* save link status information */
	if (link)
		*link = *li;

	/* flag cleared so calling functions don't call AQ again */
	pi->phy.get_link_info = false;

	return 0;
}
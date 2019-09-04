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
struct ice_link_status {int an_info; int pacing; int lse_ena; void* max_frame_size; int /*<<< orphan*/  ext_info; int /*<<< orphan*/  link_info; int /*<<< orphan*/  phy_type_low; void* link_speed; } ;
struct TYPE_4__ {int media_type; int get_link_info; struct ice_link_status link_info; struct ice_link_status link_info_old; } ;
struct ice_fc_info {int /*<<< orphan*/  current_mode; } ;
struct ice_port_info {TYPE_2__ phy; int /*<<< orphan*/  hw; int /*<<< orphan*/  lport; struct ice_fc_info fc; } ;
struct ice_aqc_get_link_status_data {int an_info; int cfg; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  ext_info; int /*<<< orphan*/  link_info; int /*<<< orphan*/  phy_type_low; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  member_0; } ;
struct ice_aqc_get_link_status {int cmd_flags; int /*<<< orphan*/  lport_num; } ;
struct TYPE_3__ {struct ice_aqc_get_link_status get_link_status; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  link_data ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_media_type { ____Placeholder_ice_media_type } ice_media_type ;

/* Variables and functions */
 int ICE_AQ_CFG_PACING_M ; 
 int ICE_AQ_LINK_PAUSE_RX ; 
 int ICE_AQ_LINK_PAUSE_TX ; 
 int /*<<< orphan*/  ICE_AQ_LSE_DIS ; 
 int /*<<< orphan*/  ICE_AQ_LSE_ENA ; 
 int /*<<< orphan*/  ICE_AQ_LSE_IS_ENABLED ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_FC_FULL ; 
 int /*<<< orphan*/  ICE_FC_NONE ; 
 int /*<<< orphan*/  ICE_FC_RX_PAUSE ; 
 int /*<<< orphan*/  ICE_FC_TX_PAUSE ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (int /*<<< orphan*/ ,struct ice_aq_desc*,struct ice_aqc_get_link_status_data*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_get_link_status ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int ice_get_media_type (struct ice_port_info*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

enum ice_status
ice_aq_get_link_info(struct ice_port_info *pi, bool ena_lse,
		     struct ice_link_status *link, struct ice_sq_cd *cd)
{
	struct ice_link_status *hw_link_info_old, *hw_link_info;
	struct ice_aqc_get_link_status_data link_data = { 0 };
	struct ice_aqc_get_link_status *resp;
	enum ice_media_type *hw_media_type;
	struct ice_fc_info *hw_fc_info;
	bool tx_pause, rx_pause;
	struct ice_aq_desc desc;
	enum ice_status status;
	u16 cmd_flags;

	if (!pi)
		return ICE_ERR_PARAM;
	hw_link_info_old = &pi->phy.link_info_old;
	hw_media_type = &pi->phy.media_type;
	hw_link_info = &pi->phy.link_info;
	hw_fc_info = &pi->fc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_link_status);
	cmd_flags = (ena_lse) ? ICE_AQ_LSE_ENA : ICE_AQ_LSE_DIS;
	resp = &desc.params.get_link_status;
	resp->cmd_flags = cpu_to_le16(cmd_flags);
	resp->lport_num = pi->lport;

	status = ice_aq_send_cmd(pi->hw, &desc, &link_data, sizeof(link_data),
				 cd);

	if (status)
		return status;

	/* save off old link status information */
	*hw_link_info_old = *hw_link_info;

	/* update current link status information */
	hw_link_info->link_speed = le16_to_cpu(link_data.link_speed);
	hw_link_info->phy_type_low = le64_to_cpu(link_data.phy_type_low);
	*hw_media_type = ice_get_media_type(pi);
	hw_link_info->link_info = link_data.link_info;
	hw_link_info->an_info = link_data.an_info;
	hw_link_info->ext_info = link_data.ext_info;
	hw_link_info->max_frame_size = le16_to_cpu(link_data.max_frame_size);
	hw_link_info->pacing = link_data.cfg & ICE_AQ_CFG_PACING_M;

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

	hw_link_info->lse_ena =
		!!(resp->cmd_flags & cpu_to_le16(ICE_AQ_LSE_IS_ENABLED));

	/* save link status information */
	if (link)
		*link = *hw_link_info;

	/* flag cleared so calling functions don't call AQ again */
	pi->phy.get_link_info = false;

	return status;
}
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
typedef  size_t u8 ;
typedef  int u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {TYPE_3__* port_info; } ;
struct ice_aqc_manage_mac_read_resp {scalar_t__ addr_type; int /*<<< orphan*/  mac_addr; } ;
struct ice_aqc_manage_mac_read {size_t num_addr; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {struct ice_aqc_manage_mac_read mac_read; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_5__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  lan_addr; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;

/* Variables and functions */
 scalar_t__ ICE_AQC_MAN_MAC_ADDR_TYPE_LAN ; 
 int ICE_AQC_MAN_MAC_LAN_ADDR_VALID ; 
 int ICE_AQC_MAN_MAC_READ_M ; 
 int /*<<< orphan*/  ICE_DBG_LAN ; 
 int ICE_ERR_BUF_TOO_SHORT ; 
 int ICE_ERR_CFG ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,void*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_manage_mac_read ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_manage_mac_read(struct ice_hw *hw, void *buf, u16 buf_size,
		       struct ice_sq_cd *cd)
{
	struct ice_aqc_manage_mac_read_resp *resp;
	struct ice_aqc_manage_mac_read *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;
	u16 flags;
	u8 i;

	cmd = &desc.params.mac_read;

	if (buf_size < sizeof(*resp))
		return ICE_ERR_BUF_TOO_SHORT;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_manage_mac_read);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	if (status)
		return status;

	resp = (struct ice_aqc_manage_mac_read_resp *)buf;
	flags = le16_to_cpu(cmd->flags) & ICE_AQC_MAN_MAC_READ_M;

	if (!(flags & ICE_AQC_MAN_MAC_LAN_ADDR_VALID)) {
		ice_debug(hw, ICE_DBG_LAN, "got invalid MAC address\n");
		return ICE_ERR_CFG;
	}

	/* A single port can report up to two (LAN and WoL) addresses */
	for (i = 0; i < cmd->num_addr; i++)
		if (resp[i].addr_type == ICE_AQC_MAN_MAC_ADDR_TYPE_LAN) {
			ether_addr_copy(hw->port_info->mac.lan_addr,
					resp[i].mac_addr);
			ether_addr_copy(hw->port_info->mac.perm_addr,
					resp[i].mac_addr);
			break;
		}

	return 0;
}
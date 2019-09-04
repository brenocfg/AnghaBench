#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  size_t u16 ;
struct ice_hw {int /*<<< orphan*/  port_info; } ;
struct ice_aqc_get_sw_cfg_resp_elem {int /*<<< orphan*/  vsi_port_num; int /*<<< orphan*/  pf_vf_num; int /*<<< orphan*/  swid; } ;
struct ice_aqc_get_sw_cfg_resp {struct ice_aqc_get_sw_cfg_resp_elem* elements; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_M ; 
 int ICE_AQC_GET_SW_CONF_RESP_IS_VF ; 
 int ICE_AQC_GET_SW_CONF_RESP_TYPE_S ; 
 int ICE_AQC_GET_SW_CONF_RESP_VSI ; 
 int ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_M ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  ICE_SW_CFG_MAX_BUF_LEN ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,void*) ; 
 struct ice_aqc_get_sw_cfg_resp* devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_aq_get_sw_cfg (struct ice_hw*,struct ice_aqc_get_sw_cfg_resp*,int /*<<< orphan*/ ,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_init_port_info (int /*<<< orphan*/ ,size_t,int,size_t,size_t,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

enum ice_status ice_get_initial_sw_cfg(struct ice_hw *hw)
{
	struct ice_aqc_get_sw_cfg_resp *rbuf;
	enum ice_status status;
	u16 req_desc = 0;
	u16 num_elems;
	u16 i;

	rbuf = devm_kzalloc(ice_hw_to_dev(hw), ICE_SW_CFG_MAX_BUF_LEN,
			    GFP_KERNEL);

	if (!rbuf)
		return ICE_ERR_NO_MEMORY;

	/* Multiple calls to ice_aq_get_sw_cfg may be required
	 * to get all the switch configuration information. The need
	 * for additional calls is indicated by ice_aq_get_sw_cfg
	 * writing a non-zero value in req_desc
	 */
	do {
		status = ice_aq_get_sw_cfg(hw, rbuf, ICE_SW_CFG_MAX_BUF_LEN,
					   &req_desc, &num_elems, NULL);

		if (status)
			break;

		for (i = 0; i < num_elems; i++) {
			struct ice_aqc_get_sw_cfg_resp_elem *ele;
			u16 pf_vf_num, swid, vsi_port_num;
			bool is_vf = false;
			u8 type;

			ele = rbuf[i].elements;
			vsi_port_num = le16_to_cpu(ele->vsi_port_num) &
				ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_M;

			pf_vf_num = le16_to_cpu(ele->pf_vf_num) &
				ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_M;

			swid = le16_to_cpu(ele->swid);

			if (le16_to_cpu(ele->pf_vf_num) &
			    ICE_AQC_GET_SW_CONF_RESP_IS_VF)
				is_vf = true;

			type = le16_to_cpu(ele->vsi_port_num) >>
				ICE_AQC_GET_SW_CONF_RESP_TYPE_S;

			if (type == ICE_AQC_GET_SW_CONF_RESP_VSI) {
				/* FW VSI is not needed. Just continue. */
				continue;
			}

			ice_init_port_info(hw->port_info, vsi_port_num,
					   type, swid, pf_vf_num, is_vf);
		}
	} while (req_desc && !status);

	devm_kfree(ice_hw_to_dev(hw), (void *)rbuf);
	return status;
}
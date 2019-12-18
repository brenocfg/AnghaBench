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
typedef  int u32 ;
struct hwrm_ver_get_output {int hwrm_intf_maj_8b; int hwrm_intf_min_8b; int hwrm_intf_upd_8b; int hwrm_fw_maj_8b; int hwrm_fw_min_8b; int hwrm_fw_bld_8b; int hwrm_fw_rsvd_8b; char* active_pkg_name; int /*<<< orphan*/  dev_caps_cfg; int /*<<< orphan*/  chip_metal; int /*<<< orphan*/  chip_rev; int /*<<< orphan*/  chip_num; int /*<<< orphan*/  max_ext_req_len; int /*<<< orphan*/  max_req_win_len; int /*<<< orphan*/  def_req_timeout; } ;
struct bnxt {int hwrm_spec_code; char* fw_ver_str; void* hwrm_max_ext_req_len; int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  fw_cap; int /*<<< orphan*/  flags; void* chip_num; void* hwrm_max_req_len; void* hwrm_cmd_timeout; int /*<<< orphan*/  dev; int /*<<< orphan*/  ver_resp; struct hwrm_ver_get_output* hwrm_cmd_resp_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_HWRM_STR_LEN ; 
 int /*<<< orphan*/  BNXT_FLAG_CHIP_NITRO_A0 ; 
 int /*<<< orphan*/  BNXT_FW_CAP_CFA_ADV_FLOW ; 
 int /*<<< orphan*/  BNXT_FW_CAP_KONG_MB_CHNL ; 
 int /*<<< orphan*/  BNXT_FW_CAP_OVS_64BIT_HANDLE ; 
 int /*<<< orphan*/  BNXT_FW_CAP_PKG_VER ; 
 int /*<<< orphan*/  BNXT_FW_CAP_SHORT_CMD ; 
 int /*<<< orphan*/  BNXT_FW_CAP_TRUSTED_VF ; 
 void* CHIP_NUM_58700 ; 
 void* DFLT_HWRM_CMD_TIMEOUT ; 
 int FW_VER_STR_LEN ; 
 void* HWRM_MAX_REQ_LEN ; 
 int VER_GET_RESP_DEV_CAPS_CFG_CFA_ADV_FLOW_MGNT_SUPPORTED ; 
 int VER_GET_RESP_DEV_CAPS_CFG_FLOW_HANDLE_64BIT_SUPPORTED ; 
 int VER_GET_RESP_DEV_CAPS_CFG_KONG_MB_CHNL_SUPPORTED ; 
 int VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_REQUIRED ; 
 int VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_SUPPORTED ; 
 int VER_GET_RESP_DEV_CAPS_CFG_TRUSTED_VF_SUPPORTED ; 
 int __bnxt_hwrm_ver_get (struct bnxt*,int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hwrm_ver_get_output*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int bnxt_hwrm_ver_get(struct bnxt *bp)
{
	struct hwrm_ver_get_output *resp = bp->hwrm_cmd_resp_addr;
	u32 dev_caps_cfg;
	int rc;

	bp->hwrm_max_req_len = HWRM_MAX_REQ_LEN;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = __bnxt_hwrm_ver_get(bp, false);
	if (rc)
		goto hwrm_ver_get_exit;

	memcpy(&bp->ver_resp, resp, sizeof(struct hwrm_ver_get_output));

	bp->hwrm_spec_code = resp->hwrm_intf_maj_8b << 16 |
			     resp->hwrm_intf_min_8b << 8 |
			     resp->hwrm_intf_upd_8b;
	if (resp->hwrm_intf_maj_8b < 1) {
		netdev_warn(bp->dev, "HWRM interface %d.%d.%d is older than 1.0.0.\n",
			    resp->hwrm_intf_maj_8b, resp->hwrm_intf_min_8b,
			    resp->hwrm_intf_upd_8b);
		netdev_warn(bp->dev, "Please update firmware with HWRM interface 1.0.0 or newer.\n");
	}
	snprintf(bp->fw_ver_str, BC_HWRM_STR_LEN, "%d.%d.%d.%d",
		 resp->hwrm_fw_maj_8b, resp->hwrm_fw_min_8b,
		 resp->hwrm_fw_bld_8b, resp->hwrm_fw_rsvd_8b);

	if (strlen(resp->active_pkg_name)) {
		int fw_ver_len = strlen(bp->fw_ver_str);

		snprintf(bp->fw_ver_str + fw_ver_len,
			 FW_VER_STR_LEN - fw_ver_len - 1, "/pkg %s",
			 resp->active_pkg_name);
		bp->fw_cap |= BNXT_FW_CAP_PKG_VER;
	}

	bp->hwrm_cmd_timeout = le16_to_cpu(resp->def_req_timeout);
	if (!bp->hwrm_cmd_timeout)
		bp->hwrm_cmd_timeout = DFLT_HWRM_CMD_TIMEOUT;

	if (resp->hwrm_intf_maj_8b >= 1) {
		bp->hwrm_max_req_len = le16_to_cpu(resp->max_req_win_len);
		bp->hwrm_max_ext_req_len = le16_to_cpu(resp->max_ext_req_len);
	}
	if (bp->hwrm_max_ext_req_len < HWRM_MAX_REQ_LEN)
		bp->hwrm_max_ext_req_len = HWRM_MAX_REQ_LEN;

	bp->chip_num = le16_to_cpu(resp->chip_num);
	if (bp->chip_num == CHIP_NUM_58700 && !resp->chip_rev &&
	    !resp->chip_metal)
		bp->flags |= BNXT_FLAG_CHIP_NITRO_A0;

	dev_caps_cfg = le32_to_cpu(resp->dev_caps_cfg);
	if ((dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_SUPPORTED) &&
	    (dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_REQUIRED))
		bp->fw_cap |= BNXT_FW_CAP_SHORT_CMD;

	if (dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_KONG_MB_CHNL_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_KONG_MB_CHNL;

	if (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_FLOW_HANDLE_64BIT_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_OVS_64BIT_HANDLE;

	if (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_TRUSTED_VF_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_TRUSTED_VF;

	if (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_CFA_ADV_FLOW_MGNT_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_CFA_ADV_FLOW;

hwrm_ver_get_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
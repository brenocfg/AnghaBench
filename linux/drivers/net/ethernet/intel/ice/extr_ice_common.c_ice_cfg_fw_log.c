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
typedef  int u8 ;
typedef  size_t u16 ;
struct TYPE_6__ {int actv_evnts; TYPE_2__* evnts; scalar_t__ uart_en; scalar_t__ cq_en; } ;
struct ice_hw {TYPE_3__ fw_log; int /*<<< orphan*/  adminq; } ;
struct ice_aqc_fw_logging_data {int /*<<< orphan*/ * entry; } ;
struct ice_aqc_fw_logging {int /*<<< orphan*/  log_ctrl; int /*<<< orphan*/  log_ctrl_valid; } ;
struct TYPE_4__ {struct ice_aqc_fw_logging fw_logging; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_5__ {int cfg; int cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQC_FW_LOG_AQ_EN ; 
 int /*<<< orphan*/  ICE_AQC_FW_LOG_AQ_VALID ; 
 size_t ICE_AQC_FW_LOG_EN_S ; 
 size_t ICE_AQC_FW_LOG_ID_M ; 
 size_t ICE_AQC_FW_LOG_ID_MAX ; 
 size_t ICE_AQC_FW_LOG_ID_S ; 
 int /*<<< orphan*/  ICE_AQC_FW_LOG_UART_EN ; 
 int /*<<< orphan*/  ICE_AQC_FW_LOG_UART_VALID ; 
 size_t ICE_AQ_FLAG_RD ; 
 int ICE_ERR_NO_MEMORY ; 
 size_t ICE_FW_LOG_DESC_SIZE (size_t) ; 
 int /*<<< orphan*/  ICE_FW_LOG_DESC_SIZE_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_fw_logging_data*) ; 
 struct ice_aqc_fw_logging_data* devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_fw_logging ; 
 int /*<<< orphan*/  ice_check_sq_alive (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int ice_get_fw_log_cfg (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status ice_cfg_fw_log(struct ice_hw *hw, bool enable)
{
	struct ice_aqc_fw_logging_data *data = NULL;
	struct ice_aqc_fw_logging *cmd;
	enum ice_status status = 0;
	u16 i, chgs = 0, len = 0;
	struct ice_aq_desc desc;
	u8 actv_evnts = 0;
	void *buf = NULL;

	if (!hw->fw_log.cq_en && !hw->fw_log.uart_en)
		return 0;

	/* Disable FW logging only when the control queue is still responsive */
	if (!enable &&
	    (!hw->fw_log.actv_evnts || !ice_check_sq_alive(hw, &hw->adminq)))
		return 0;

	/* Get current FW log settings */
	status = ice_get_fw_log_cfg(hw);
	if (status)
		return status;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_fw_logging);
	cmd = &desc.params.fw_logging;

	/* Indicate which controls are valid */
	if (hw->fw_log.cq_en)
		cmd->log_ctrl_valid |= ICE_AQC_FW_LOG_AQ_VALID;

	if (hw->fw_log.uart_en)
		cmd->log_ctrl_valid |= ICE_AQC_FW_LOG_UART_VALID;

	if (enable) {
		/* Fill in an array of entries with FW logging modules and
		 * logging events being reconfigured.
		 */
		for (i = 0; i < ICE_AQC_FW_LOG_ID_MAX; i++) {
			u16 val;

			/* Keep track of enabled event types */
			actv_evnts |= hw->fw_log.evnts[i].cfg;

			if (hw->fw_log.evnts[i].cfg == hw->fw_log.evnts[i].cur)
				continue;

			if (!data) {
				data = devm_kzalloc(ice_hw_to_dev(hw),
						    ICE_FW_LOG_DESC_SIZE_MAX,
						    GFP_KERNEL);
				if (!data)
					return ICE_ERR_NO_MEMORY;
			}

			val = i << ICE_AQC_FW_LOG_ID_S;
			val |= hw->fw_log.evnts[i].cfg << ICE_AQC_FW_LOG_EN_S;
			data->entry[chgs++] = cpu_to_le16(val);
		}

		/* Only enable FW logging if at least one module is specified.
		 * If FW logging is currently enabled but all modules are not
		 * enabled to emit log messages, disable FW logging altogether.
		 */
		if (actv_evnts) {
			/* Leave if there is effectively no change */
			if (!chgs)
				goto out;

			if (hw->fw_log.cq_en)
				cmd->log_ctrl |= ICE_AQC_FW_LOG_AQ_EN;

			if (hw->fw_log.uart_en)
				cmd->log_ctrl |= ICE_AQC_FW_LOG_UART_EN;

			buf = data;
			len = ICE_FW_LOG_DESC_SIZE(chgs);
			desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
		}
	}

	status = ice_aq_send_cmd(hw, &desc, buf, len, NULL);
	if (!status) {
		/* Update the current configuration to reflect events enabled.
		 * hw->fw_log.cq_en and hw->fw_log.uart_en indicate if the FW
		 * logging mode is enabled for the device. They do not reflect
		 * actual modules being enabled to emit log messages. So, their
		 * values remain unchanged even when all modules are disabled.
		 */
		u16 cnt = enable ? chgs : (u16)ICE_AQC_FW_LOG_ID_MAX;

		hw->fw_log.actv_evnts = actv_evnts;
		for (i = 0; i < cnt; i++) {
			u16 v, m;

			if (!enable) {
				/* When disabling all FW logging events as part
				 * of device's de-initialization, the original
				 * configurations are retained, and can be used
				 * to reconfigure FW logging later if the device
				 * is re-initialized.
				 */
				hw->fw_log.evnts[i].cur = 0;
				continue;
			}

			v = le16_to_cpu(data->entry[i]);
			m = (v & ICE_AQC_FW_LOG_ID_M) >> ICE_AQC_FW_LOG_ID_S;
			hw->fw_log.evnts[m].cur = hw->fw_log.evnts[m].cfg;
		}
	}

out:
	if (data)
		devm_kfree(ice_hw_to_dev(hw), data);

	return status;
}
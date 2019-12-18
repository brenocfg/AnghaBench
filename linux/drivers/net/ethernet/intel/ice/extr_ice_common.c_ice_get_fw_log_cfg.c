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
typedef  size_t u16 ;
struct TYPE_4__ {TYPE_1__* evnts; } ;
struct ice_hw {TYPE_2__ fw_log; } ;
struct ice_aqc_fw_logging_data {int /*<<< orphan*/ * entry; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_3__ {size_t cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t ICE_AQC_FW_LOG_EN_M ; 
 size_t ICE_AQC_FW_LOG_EN_S ; 
 size_t ICE_AQC_FW_LOG_ID_M ; 
 size_t ICE_AQC_FW_LOG_ID_MAX ; 
 size_t ICE_AQC_FW_LOG_ID_S ; 
 int /*<<< orphan*/  ICE_AQ_FLAG_BUF ; 
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int ICE_ERR_NO_MEMORY ; 
 size_t ICE_FW_LOG_DESC_SIZE_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_fw_logging_data*) ; 
 struct ice_aqc_fw_logging_data* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_fw_logging_data*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_fw_logging_info ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status ice_get_fw_log_cfg(struct ice_hw *hw)
{
	struct ice_aqc_fw_logging_data *config;
	struct ice_aq_desc desc;
	enum ice_status status;
	u16 size;

	size = ICE_FW_LOG_DESC_SIZE_MAX;
	config = devm_kzalloc(ice_hw_to_dev(hw), size, GFP_KERNEL);
	if (!config)
		return ICE_ERR_NO_MEMORY;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_fw_logging_info);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	status = ice_aq_send_cmd(hw, &desc, config, size, NULL);
	if (!status) {
		u16 i;

		/* Save FW logging information into the HW structure */
		for (i = 0; i < ICE_AQC_FW_LOG_ID_MAX; i++) {
			u16 v, m, flgs;

			v = le16_to_cpu(config->entry[i]);
			m = (v & ICE_AQC_FW_LOG_ID_M) >> ICE_AQC_FW_LOG_ID_S;
			flgs = (v & ICE_AQC_FW_LOG_EN_M) >> ICE_AQC_FW_LOG_EN_S;

			if (m < ICE_AQC_FW_LOG_ID_MAX)
				hw->fw_log.evnts[m].cur = flgs;
		}
	}

	devm_kfree(ice_hw_to_dev(hw), config);

	return status;
}
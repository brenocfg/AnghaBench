#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct temp_report_ths_cmd {int /*<<< orphan*/ * thresholds; int /*<<< orphan*/  num_temps; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__* temp_trips; int* fw_trips_index; int /*<<< orphan*/  tzone; } ;
struct iwl_mvm {TYPE_1__ tz_device; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int IWL_MAX_DTS_TRIPS ; 
 int /*<<< orphan*/  PHY_OPS_GROUP ; 
 scalar_t__ S16_MIN ; 
 int /*<<< orphan*/  TEMP_REPORTING_THRESHOLDS_CMD ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_temps ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct temp_report_ths_cmd*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_send_temp_report_ths_cmd(struct iwl_mvm *mvm)
{
	struct temp_report_ths_cmd cmd = {0};
	int ret;
#ifdef CONFIG_THERMAL
	int i, j, idx = 0;

	lockdep_assert_held(&mvm->mutex);

	if (!mvm->tz_device.tzone)
		goto send;

	/* The driver holds array of temperature trips that are unsorted
	 * and uncompressed, the FW should get it compressed and sorted
	 */

	/* compress temp_trips to cmd array, remove uninitialized values*/
	for (i = 0; i < IWL_MAX_DTS_TRIPS; i++) {
		if (mvm->tz_device.temp_trips[i] != S16_MIN) {
			cmd.thresholds[idx++] =
				cpu_to_le16(mvm->tz_device.temp_trips[i]);
		}
	}
	cmd.num_temps = cpu_to_le32(idx);

	if (!idx)
		goto send;

	/*sort cmd array*/
	sort(cmd.thresholds, idx, sizeof(s16), compare_temps, NULL);

	/* we should save the indexes of trips because we sort
	 * and compress the orginal array
	 */
	for (i = 0; i < idx; i++) {
		for (j = 0; j < IWL_MAX_DTS_TRIPS; j++) {
			if (le16_to_cpu(cmd.thresholds[i]) ==
				mvm->tz_device.temp_trips[j])
				mvm->tz_device.fw_trips_index[i] = j;
		}
	}

send:
#endif
	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(PHY_OPS_GROUP,
						TEMP_REPORTING_THRESHOLDS_CMD),
				   0, sizeof(cmd), &cmd);
	if (ret)
		IWL_ERR(mvm, "TEMP_REPORT_THS_CMD command failed (err=%d)\n",
			ret);

	return ret;
}
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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_thermal_device {int /*<<< orphan*/ * fw_trips_index; scalar_t__ tzone; } ;
struct iwl_mvm {struct iwl_mvm_thermal_device tz_device; int /*<<< orphan*/  status; } ;
struct iwl_dts_measurement_notif_v2 {int /*<<< orphan*/  threshold_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_mvm*,char*,int,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int IWL_MAX_DTS_TRIPS ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_CTKILL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_is_tt_in_fw (struct iwl_mvm*) ; 
 int iwl_mvm_temp_notif_parse (struct iwl_mvm*,struct iwl_rx_packet*) ; 
 int /*<<< orphan*/  iwl_mvm_tt_temp_changed (struct iwl_mvm*,int) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_notify_framework (scalar_t__,int /*<<< orphan*/ ) ; 

void iwl_mvm_temp_notif(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_dts_measurement_notif_v2 *notif_v2;
	int len = iwl_rx_packet_payload_len(pkt);
	int temp;
	u32 ths_crossed;

	/* the notification is handled synchronously in ctkill, so skip here */
	if (test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		return;

	temp = iwl_mvm_temp_notif_parse(mvm, pkt);

	if (!iwl_mvm_is_tt_in_fw(mvm)) {
		if (temp >= 0)
			iwl_mvm_tt_temp_changed(mvm, temp);
		return;
	}

	if (WARN_ON_ONCE(len < sizeof(*notif_v2))) {
		IWL_ERR(mvm, "Invalid DTS_MEASUREMENT_NOTIFICATION\n");
		return;
	}

	notif_v2 = (void *)pkt->data;
	ths_crossed = le32_to_cpu(notif_v2->threshold_idx);

	/* 0xFF in ths_crossed means the notification is not related
	 * to a trip, so we can ignore it here.
	 */
	if (ths_crossed == 0xFF)
		return;

	IWL_DEBUG_TEMP(mvm, "Temp = %d Threshold crossed = %d\n",
		       temp, ths_crossed);

#ifdef CONFIG_THERMAL
	if (WARN_ON(ths_crossed >= IWL_MAX_DTS_TRIPS))
		return;

	if (mvm->tz_device.tzone) {
		struct iwl_mvm_thermal_device *tz_dev = &mvm->tz_device;

		thermal_notify_framework(tz_dev->tzone,
					 tz_dev->fw_trips_index[ths_crossed]);
	}
#endif /* CONFIG_THERMAL */
}
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
typedef  int u16 ;
struct wmi_tlv_tx_bundle_compl_parse {int desc_ids_done; int status_done; int ppdu_ids_done; int ack_rssi_done; void const* ack_rssi; void const* ppdu_ids; void const* status; void const* desc_ids; void const* num_reports; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
#define  WMI_TLV_TAG_ARRAY_UINT32 129 
#define  WMI_TLV_TAG_STRUCT_MGMT_TX_COMPL_BUNDLE_EVENT 128 

__attribute__((used)) static int
ath10k_wmi_tlv_mgmt_tx_bundle_compl_parse(struct ath10k *ar, u16 tag, u16 len,
					  const void *ptr, void *data)
{
	struct wmi_tlv_tx_bundle_compl_parse *bundle_tx_compl = data;

	switch (tag) {
	case WMI_TLV_TAG_STRUCT_MGMT_TX_COMPL_BUNDLE_EVENT:
		bundle_tx_compl->num_reports = ptr;
		break;
	case WMI_TLV_TAG_ARRAY_UINT32:
		if (!bundle_tx_compl->desc_ids_done) {
			bundle_tx_compl->desc_ids_done = true;
			bundle_tx_compl->desc_ids = ptr;
		} else if (!bundle_tx_compl->status_done) {
			bundle_tx_compl->status_done = true;
			bundle_tx_compl->status = ptr;
		} else if (!bundle_tx_compl->ppdu_ids_done) {
			bundle_tx_compl->ppdu_ids_done = true;
			bundle_tx_compl->ppdu_ids = ptr;
		} else if (!bundle_tx_compl->ack_rssi_done) {
			bundle_tx_compl->ack_rssi_done = true;
			bundle_tx_compl->ack_rssi = ptr;
		}
		break;
	default:
		break;
	}
	return 0;
}
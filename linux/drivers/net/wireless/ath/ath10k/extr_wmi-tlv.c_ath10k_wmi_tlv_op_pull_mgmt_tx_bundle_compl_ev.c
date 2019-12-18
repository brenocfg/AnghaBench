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
struct wmi_tlv_tx_bundle_compl_parse {int /*<<< orphan*/  ack_rssi; int /*<<< orphan*/  ppdu_ids; scalar_t__ status; scalar_t__ desc_ids; int /*<<< orphan*/ * num_reports; } ;
struct wmi_tlv_mgmt_tx_bundle_compl_ev_arg {int /*<<< orphan*/  ack_rssi; int /*<<< orphan*/  ppdu_ids; scalar_t__ status; scalar_t__ desc_ids; int /*<<< orphan*/  num_reports; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  WMI_SERVICE_TX_DATA_ACK_RSSI ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_tlv_iter (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_tlv_tx_bundle_compl_parse*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_mgmt_tx_bundle_compl_parse ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_mgmt_tx_bundle_compl_ev(
				struct ath10k *ar, struct sk_buff *skb,
				struct wmi_tlv_mgmt_tx_bundle_compl_ev_arg *arg)
{
	struct wmi_tlv_tx_bundle_compl_parse bundle_tx_compl = { };
	int ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_mgmt_tx_bundle_compl_parse,
				  &bundle_tx_compl);
	if (ret) {
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	if (!bundle_tx_compl.num_reports || !bundle_tx_compl.desc_ids ||
	    !bundle_tx_compl.status)
		return -EPROTO;

	arg->num_reports = *bundle_tx_compl.num_reports;
	arg->desc_ids = bundle_tx_compl.desc_ids;
	arg->status = bundle_tx_compl.status;
	arg->ppdu_ids = bundle_tx_compl.ppdu_ids;

	if (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
		arg->ack_rssi = bundle_tx_compl.ack_rssi;

	return 0;
}
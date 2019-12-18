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
struct wmi_ch_info_ev_arg {int /*<<< orphan*/  mac_clk_mhz; int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  rx_clear_count; int /*<<< orphan*/  noise_floor; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  freq; int /*<<< orphan*/  err_code; } ;
struct sk_buff {int dummy; } ;
struct chan_info_params {void* cycle_count; void* rx_clear_count; void* noise_floor; void* cmd_flags; void* freq; void* err_code; void* mac_clk_mhz; } ;
struct TYPE_4__ {int state; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_3__* running_fw; TYPE_1__ scan; } ;
struct TYPE_5__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_6__ {TYPE_2__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL ; 
#define  ATH10K_SCAN_ABORTING 131 
#define  ATH10K_SCAN_IDLE 130 
#define  ATH10K_SCAN_RUNNING 129 
#define  ATH10K_SCAN_STARTING 128 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,void*,void*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  ath10k_wmi_event_chan_info_paired (struct ath10k*,struct chan_info_params*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_chan_info_unpaired (struct ath10k*,struct chan_info_params*) ; 
 int ath10k_wmi_pull_ch_info (struct ath10k*,struct sk_buff*,struct wmi_ch_info_ev_arg*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath10k_wmi_event_chan_info(struct ath10k *ar, struct sk_buff *skb)
{
	struct chan_info_params ch_info_param;
	struct wmi_ch_info_ev_arg arg = {};
	int ret;

	ret = ath10k_wmi_pull_ch_info(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse chan info event: %d\n", ret);
		return;
	}

	ch_info_param.err_code = __le32_to_cpu(arg.err_code);
	ch_info_param.freq = __le32_to_cpu(arg.freq);
	ch_info_param.cmd_flags = __le32_to_cpu(arg.cmd_flags);
	ch_info_param.noise_floor = __le32_to_cpu(arg.noise_floor);
	ch_info_param.rx_clear_count = __le32_to_cpu(arg.rx_clear_count);
	ch_info_param.cycle_count = __le32_to_cpu(arg.cycle_count);
	ch_info_param.mac_clk_mhz = __le32_to_cpu(arg.mac_clk_mhz);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "chan info err_code %d freq %d cmd_flags %d noise_floor %d rx_clear_count %d cycle_count %d\n",
		   ch_info_param.err_code, ch_info_param.freq, ch_info_param.cmd_flags,
		   ch_info_param.noise_floor, ch_info_param.rx_clear_count,
		   ch_info_param.cycle_count);

	spin_lock_bh(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH10K_SCAN_IDLE:
	case ATH10K_SCAN_STARTING:
		ath10k_warn(ar, "received chan info event without a scan request, ignoring\n");
		goto exit;
	case ATH10K_SCAN_RUNNING:
	case ATH10K_SCAN_ABORTING:
		break;
	}

	if (test_bit(ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL,
		     ar->running_fw->fw_file.fw_features))
		ath10k_wmi_event_chan_info_unpaired(ar, &ch_info_param);
	else
		ath10k_wmi_event_chan_info_paired(ar, &ch_info_param);

exit:
	spin_unlock_bh(&ar->data_lock);
}
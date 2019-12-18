#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wmi_bb_timing_cfg_arg {int /*<<< orphan*/  member_0; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  svc_map; TYPE_1__* pdev_param; } ;
struct ath10k {int state; int ani_enabled; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  radar_conf_state; scalar_t__ num_started_vdevs; TYPE_4__ wmi; int /*<<< orphan*/  dev_flags; TYPE_3__* running_fw; int /*<<< orphan*/  cfg_rx_chainmask; int /*<<< orphan*/  cfg_tx_chainmask; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  normal_mode_fw; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_7__ {TYPE_2__ fw_file; } ;
struct TYPE_5__ {int /*<<< orphan*/  enable_btcoex; int /*<<< orphan*/  peer_stats_update_period; int /*<<< orphan*/  ani_enable; int /*<<< orphan*/  arp_ac_override; int /*<<< orphan*/  idle_ps_config; int /*<<< orphan*/  burst_enable; int /*<<< orphan*/  dynamic_bw; int /*<<< orphan*/  pmf_qos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FIRMWARE_MODE_NORMAL ; 
 int /*<<< orphan*/  ATH10K_FLAG_BTCOEX ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_BTCOEX_PARAM ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_SUPPORTS_ADAPTIVE_CCA ; 
 int /*<<< orphan*/  ATH10K_RADAR_CONFIRMATION_IDLE ; 
#define  ATH10K_STATE_OFF 133 
#define  ATH10K_STATE_ON 132 
#define  ATH10K_STATE_RESTARTED 131 
#define  ATH10K_STATE_RESTARTING 130 
#define  ATH10K_STATE_UTF 129 
#define  ATH10K_STATE_WEDGED 128 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PEER_DEFAULT_STATS_UPDATE_PERIOD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_CCA_DETECT_LEVEL_AUTO ; 
 int /*<<< orphan*/  WMI_CCA_DETECT_MARGIN_AUTO ; 
 int /*<<< orphan*/  WMI_SERVICE_ADAPTIVE_OCS ; 
 int /*<<< orphan*/  WMI_SERVICE_BB_TIMING_CONFIG_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_BURST ; 
 int /*<<< orphan*/  WMI_SERVICE_COEX_GPIO ; 
 int /*<<< orphan*/  WMI_SERVICE_SPOOF_MAC_SUPPORT ; 
 int __ath10k_fetch_bb_timing_dt (struct ath10k*,struct wmi_bb_timing_cfg_arg*) ; 
 int /*<<< orphan*/  __ath10k_set_antenna (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_core_start (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_core_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_drain_tx (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_hif_power_down (struct ath10k*) ; 
 int ath10k_hif_power_up (struct ath10k*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_peer_stats_enabled (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_regd_update (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_spectral_start (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_thermal_set_throttling (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_adaptive_qcs (struct ath10k*,int) ; 
 int ath10k_wmi_pdev_bb_timing (struct ath10k*,struct wmi_bb_timing_cfg_arg*) ; 
 int ath10k_wmi_pdev_enable_adaptive_cca (struct ath10k*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_pdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_scan_prob_req_oui (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_start(struct ieee80211_hw *hw)
{
	struct ath10k *ar = hw->priv;
	u32 param;
	int ret = 0;
	struct wmi_bb_timing_cfg_arg bb_timing = {0};

	/*
	 * This makes sense only when restarting hw. It is harmless to call
	 * unconditionally. This is necessary to make sure no HTT/WMI tx
	 * commands will be submitted while restarting.
	 */
	ath10k_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);

	switch (ar->state) {
	case ATH10K_STATE_OFF:
		ar->state = ATH10K_STATE_ON;
		break;
	case ATH10K_STATE_RESTARTING:
		ar->state = ATH10K_STATE_RESTARTED;
		break;
	case ATH10K_STATE_ON:
	case ATH10K_STATE_RESTARTED:
	case ATH10K_STATE_WEDGED:
		WARN_ON(1);
		ret = -EINVAL;
		goto err;
	case ATH10K_STATE_UTF:
		ret = -EBUSY;
		goto err;
	}

	ret = ath10k_hif_power_up(ar, ATH10K_FIRMWARE_MODE_NORMAL);
	if (ret) {
		ath10k_err(ar, "Could not init hif: %d\n", ret);
		goto err_off;
	}

	ret = ath10k_core_start(ar, ATH10K_FIRMWARE_MODE_NORMAL,
				&ar->normal_mode_fw);
	if (ret) {
		ath10k_err(ar, "Could not init core: %d\n", ret);
		goto err_power_down;
	}

	param = ar->wmi.pdev_param->pmf_qos;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	if (ret) {
		ath10k_warn(ar, "failed to enable PMF QOS: %d\n", ret);
		goto err_core_stop;
	}

	param = ar->wmi.pdev_param->dynamic_bw;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	if (ret) {
		ath10k_warn(ar, "failed to enable dynamic BW: %d\n", ret);
		goto err_core_stop;
	}

	if (test_bit(WMI_SERVICE_SPOOF_MAC_SUPPORT, ar->wmi.svc_map)) {
		ret = ath10k_wmi_scan_prob_req_oui(ar, ar->mac_addr);
		if (ret) {
			ath10k_err(ar, "failed to set prob req oui: %i\n", ret);
			goto err_core_stop;
		}
	}

	if (test_bit(WMI_SERVICE_ADAPTIVE_OCS, ar->wmi.svc_map)) {
		ret = ath10k_wmi_adaptive_qcs(ar, true);
		if (ret) {
			ath10k_warn(ar, "failed to enable adaptive qcs: %d\n",
				    ret);
			goto err_core_stop;
		}
	}

	if (test_bit(WMI_SERVICE_BURST, ar->wmi.svc_map)) {
		param = ar->wmi.pdev_param->burst_enable;
		ret = ath10k_wmi_pdev_set_param(ar, param, 0);
		if (ret) {
			ath10k_warn(ar, "failed to disable burst: %d\n", ret);
			goto err_core_stop;
		}
	}

	param = ar->wmi.pdev_param->idle_ps_config;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	if (ret && ret != -EOPNOTSUPP) {
		ath10k_warn(ar, "failed to enable idle_ps_config: %d\n", ret);
		goto err_core_stop;
	}

	__ath10k_set_antenna(ar, ar->cfg_tx_chainmask, ar->cfg_rx_chainmask);

	/*
	 * By default FW set ARP frames ac to voice (6). In that case ARP
	 * exchange is not working properly for UAPSD enabled AP. ARP requests
	 * which arrives with access category 0 are processed by network stack
	 * and send back with access category 0, but FW changes access category
	 * to 6. Set ARP frames access category to best effort (0) solves
	 * this problem.
	 */

	param = ar->wmi.pdev_param->arp_ac_override;
	ret = ath10k_wmi_pdev_set_param(ar, param, 0);
	if (ret) {
		ath10k_warn(ar, "failed to set arp ac override parameter: %d\n",
			    ret);
		goto err_core_stop;
	}

	if (test_bit(ATH10K_FW_FEATURE_SUPPORTS_ADAPTIVE_CCA,
		     ar->running_fw->fw_file.fw_features)) {
		ret = ath10k_wmi_pdev_enable_adaptive_cca(ar, 1,
							  WMI_CCA_DETECT_LEVEL_AUTO,
							  WMI_CCA_DETECT_MARGIN_AUTO);
		if (ret) {
			ath10k_warn(ar, "failed to enable adaptive cca: %d\n",
				    ret);
			goto err_core_stop;
		}
	}

	param = ar->wmi.pdev_param->ani_enable;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	if (ret) {
		ath10k_warn(ar, "failed to enable ani by default: %d\n",
			    ret);
		goto err_core_stop;
	}

	ar->ani_enabled = true;

	if (ath10k_peer_stats_enabled(ar)) {
		param = ar->wmi.pdev_param->peer_stats_update_period;
		ret = ath10k_wmi_pdev_set_param(ar, param,
						PEER_DEFAULT_STATS_UPDATE_PERIOD);
		if (ret) {
			ath10k_warn(ar,
				    "failed to set peer stats period : %d\n",
				    ret);
			goto err_core_stop;
		}
	}

	param = ar->wmi.pdev_param->enable_btcoex;
	if (test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map) &&
	    test_bit(ATH10K_FW_FEATURE_BTCOEX_PARAM,
		     ar->running_fw->fw_file.fw_features)) {
		ret = ath10k_wmi_pdev_set_param(ar, param, 0);
		if (ret) {
			ath10k_warn(ar,
				    "failed to set btcoex param: %d\n", ret);
			goto err_core_stop;
		}
		clear_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags);
	}

	if (test_bit(WMI_SERVICE_BB_TIMING_CONFIG_SUPPORT, ar->wmi.svc_map)) {
		ret = __ath10k_fetch_bb_timing_dt(ar, &bb_timing);
		if (!ret) {
			ret = ath10k_wmi_pdev_bb_timing(ar, &bb_timing);
			if (ret) {
				ath10k_warn(ar,
					    "failed to set bb timings: %d\n",
					    ret);
				goto err_core_stop;
			}
		}
	}

	ar->num_started_vdevs = 0;
	ath10k_regd_update(ar);

	ath10k_spectral_start(ar);
	ath10k_thermal_set_throttling(ar);

	ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_IDLE;

	mutex_unlock(&ar->conf_mutex);
	return 0;

err_core_stop:
	ath10k_core_stop(ar);

err_power_down:
	ath10k_hif_power_down(ar);

err_off:
	ar->state = ATH10K_STATE_OFF;

err:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}
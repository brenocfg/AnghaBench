#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_23__ {int /*<<< orphan*/  fw_features; } ;
struct ath10k_fw_components {TYPE_6__ fw_file; } ;
struct TYPE_20__ {int in_ord_rx; } ;
struct TYPE_26__ {TYPE_3__ rx_ring; } ;
struct TYPE_25__ {scalar_t__ hw_filter_reset_required; } ;
struct TYPE_24__ {int /*<<< orphan*/  svc_map; } ;
struct TYPE_19__ {int /*<<< orphan*/  target_send_suspend_complete; } ;
struct TYPE_17__ {TYPE_2__ htc_ops; } ;
struct TYPE_18__ {scalar_t__ bus; } ;
struct ath10k {int max_num_vdevs; int free_vdev_map; TYPE_9__ htt; int /*<<< orphan*/  arvifs; TYPE_8__ hw_params; int /*<<< orphan*/  mac_addr; TYPE_7__ wmi; struct ath10k_fw_components const* running_fw; TYPE_5__* hw; TYPE_15__ htc; TYPE_1__ hif; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum ath10k_firmware_mode { ____Placeholder_ath10k_firmware_mode } ath10k_firmware_mode ;
struct TYPE_22__ {TYPE_4__* wiphy; } ;
struct TYPE_21__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 scalar_t__ ATH10K_BUS_SDIO ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ATH10K_FIRMWARE_MODE_NORMAL ; 
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_BTCOEX_PARAM ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_NON_BMI ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_SUPPORTS_SKIP_CLOCK_INIT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMI_10_4_BSS_CHANNEL_INFO_64 ; 
 int /*<<< orphan*/  WMI_10_4_COEX_GPIO_SUPPORT ; 
 int /*<<< orphan*/  WMI_10_4_PEER_STATS ; 
 int /*<<< orphan*/  WMI_10_4_REPORT_AIRTIME ; 
 int /*<<< orphan*/  WMI_10_4_TDLS_EXPLICIT_MODE_ONLY ; 
 int /*<<< orphan*/  WMI_10_4_TDLS_UAPSD_BUFFER_STA ; 
 int /*<<< orphan*/  WMI_10_4_TX_DATA_ACK_RSSI ; 
 int /*<<< orphan*/  WMI_10_4_VDEV_STATS ; 
 int /*<<< orphan*/  WMI_SERVICE_BSS_CHANNEL_INFO_64 ; 
 int /*<<< orphan*/  WMI_SERVICE_COEX_GPIO ; 
 int /*<<< orphan*/  WMI_SERVICE_EXT_RES_CFG_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_REPORT_AIRTIME ; 
 int /*<<< orphan*/  WMI_SERVICE_RX_FULL_REORDER ; 
 int /*<<< orphan*/  WMI_SERVICE_TDLS_EXPLICIT_MODE_ONLY ; 
 int /*<<< orphan*/  WMI_SERVICE_TDLS_UAPSD_BUFFER_STA ; 
 int /*<<< orphan*/  WMI_SERVICE_TX_DATA_ACK_RSSI ; 
 int ath10k_bmi_done (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_bmi_start (struct ath10k*) ; 
 int ath10k_bmi_write32 (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int ath10k_core_compat_services (struct ath10k*) ; 
 int ath10k_core_reset_rx_filter (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ath10k_debug_start (struct ath10k*) ; 
 int ath10k_download_cal_data (struct ath10k*) ; 
 int ath10k_download_fw (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 int ath10k_hif_set_target_log_mode (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_hif_start (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_hif_stop (struct ath10k*) ; 
 int ath10k_hif_swap_mailbox (struct ath10k*) ; 
 int ath10k_htc_init (struct ath10k*) ; 
 int ath10k_htc_start (TYPE_15__*) ; 
 int ath10k_htc_wait_target (TYPE_15__*) ; 
 int ath10k_htt_connect (TYPE_9__*) ; 
 int ath10k_htt_init (struct ath10k*) ; 
 int ath10k_htt_rx_alloc (TYPE_9__*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_free (TYPE_9__*) ; 
 int ath10k_htt_rx_ring_refill (struct ath10k*) ; 
 int ath10k_htt_setup (TYPE_9__*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_free (TYPE_9__*) ; 
 int ath10k_htt_tx_start (TYPE_9__*) ; 
 scalar_t__ ath10k_init_configure_target (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_init_sdio (struct ath10k*,int) ; 
 int ath10k_init_uart (struct ath10k*) ; 
 int ath10k_mac_ext_resource_config (struct ath10k*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_peer_stats_enabled (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_send_suspend_complete ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_attach (struct ath10k*) ; 
 int ath10k_wmi_cmd_init (struct ath10k*) ; 
 int ath10k_wmi_connect (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_detach (struct ath10k*) ; 
 int ath10k_wmi_pdev_set_base_macaddr (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_wait_for_service_ready (struct ath10k*) ; 
 int ath10k_wmi_wait_for_unified_ready (struct ath10k*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_diag_log ; 
 int /*<<< orphan*/  hi_skip_clock_init ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_core_start(struct ath10k *ar, enum ath10k_firmware_mode mode,
		      const struct ath10k_fw_components *fw)
{
	int status;
	u32 val;

	lockdep_assert_held(&ar->conf_mutex);

	clear_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags);

	ar->running_fw = fw;

	if (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->running_fw->fw_file.fw_features)) {
		ath10k_bmi_start(ar);

		if (ath10k_init_configure_target(ar)) {
			status = -EINVAL;
			goto err;
		}

		status = ath10k_download_cal_data(ar);
		if (status)
			goto err;

		/* Some of of qca988x solutions are having global reset issue
		 * during target initialization. Bypassing PLL setting before
		 * downloading firmware and letting the SoC run on REF_CLK is
		 * fixing the problem. Corresponding firmware change is also
		 * needed to set the clock source once the target is
		 * initialized.
		 */
		if (test_bit(ATH10K_FW_FEATURE_SUPPORTS_SKIP_CLOCK_INIT,
			     ar->running_fw->fw_file.fw_features)) {
			status = ath10k_bmi_write32(ar, hi_skip_clock_init, 1);
			if (status) {
				ath10k_err(ar, "could not write to skip_clock_init: %d\n",
					   status);
				goto err;
			}
		}

		status = ath10k_download_fw(ar);
		if (status)
			goto err;

		status = ath10k_init_uart(ar);
		if (status)
			goto err;

		if (ar->hif.bus == ATH10K_BUS_SDIO)
			ath10k_init_sdio(ar, mode);
	}

	ar->htc.htc_ops.target_send_suspend_complete =
		ath10k_send_suspend_complete;

	status = ath10k_htc_init(ar);
	if (status) {
		ath10k_err(ar, "could not init HTC (%d)\n", status);
		goto err;
	}

	if (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->running_fw->fw_file.fw_features)) {
		status = ath10k_bmi_done(ar);
		if (status)
			goto err;
	}

	status = ath10k_wmi_attach(ar);
	if (status) {
		ath10k_err(ar, "WMI attach failed: %d\n", status);
		goto err;
	}

	status = ath10k_htt_init(ar);
	if (status) {
		ath10k_err(ar, "failed to init htt: %d\n", status);
		goto err_wmi_detach;
	}

	status = ath10k_htt_tx_start(&ar->htt);
	if (status) {
		ath10k_err(ar, "failed to alloc htt tx: %d\n", status);
		goto err_wmi_detach;
	}

	/* If firmware indicates Full Rx Reorder support it must be used in a
	 * slightly different manner. Let HTT code know.
	 */
	ar->htt.rx_ring.in_ord_rx = !!(test_bit(WMI_SERVICE_RX_FULL_REORDER,
						ar->wmi.svc_map));

	status = ath10k_htt_rx_alloc(&ar->htt);
	if (status) {
		ath10k_err(ar, "failed to alloc htt rx: %d\n", status);
		goto err_htt_tx_detach;
	}

	status = ath10k_hif_start(ar);
	if (status) {
		ath10k_err(ar, "could not start HIF: %d\n", status);
		goto err_htt_rx_detach;
	}

	status = ath10k_htc_wait_target(&ar->htc);
	if (status) {
		ath10k_err(ar, "failed to connect to HTC: %d\n", status);
		goto err_hif_stop;
	}

	status = ath10k_hif_swap_mailbox(ar);
	if (status) {
		ath10k_err(ar, "failed to swap mailbox: %d\n", status);
		goto err_hif_stop;
	}

	if (mode == ATH10K_FIRMWARE_MODE_NORMAL) {
		status = ath10k_htt_connect(&ar->htt);
		if (status) {
			ath10k_err(ar, "failed to connect htt (%d)\n", status);
			goto err_hif_stop;
		}
	}

	status = ath10k_wmi_connect(ar);
	if (status) {
		ath10k_err(ar, "could not connect wmi: %d\n", status);
		goto err_hif_stop;
	}

	status = ath10k_htc_start(&ar->htc);
	if (status) {
		ath10k_err(ar, "failed to start htc: %d\n", status);
		goto err_hif_stop;
	}

	if (mode == ATH10K_FIRMWARE_MODE_NORMAL) {
		status = ath10k_wmi_wait_for_service_ready(ar);
		if (status) {
			ath10k_warn(ar, "wmi service ready event not received");
			goto err_hif_stop;
		}
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "firmware %s booted\n",
		   ar->hw->wiphy->fw_version);

	if (test_bit(WMI_SERVICE_EXT_RES_CFG_SUPPORT, ar->wmi.svc_map) &&
	    mode == ATH10K_FIRMWARE_MODE_NORMAL) {
		val = 0;
		if (ath10k_peer_stats_enabled(ar))
			val = WMI_10_4_PEER_STATS;

		/* Enable vdev stats by default */
		val |= WMI_10_4_VDEV_STATS;

		if (test_bit(WMI_SERVICE_BSS_CHANNEL_INFO_64, ar->wmi.svc_map))
			val |= WMI_10_4_BSS_CHANNEL_INFO_64;

		/* 10.4 firmware supports BT-Coex without reloading firmware
		 * via pdev param. To support Bluetooth coexistence pdev param,
		 * WMI_COEX_GPIO_SUPPORT of extended resource config should be
		 * enabled always.
		 */
		if (test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map) &&
		    test_bit(ATH10K_FW_FEATURE_BTCOEX_PARAM,
			     ar->running_fw->fw_file.fw_features))
			val |= WMI_10_4_COEX_GPIO_SUPPORT;

		if (test_bit(WMI_SERVICE_TDLS_EXPLICIT_MODE_ONLY,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TDLS_EXPLICIT_MODE_ONLY;

		if (test_bit(WMI_SERVICE_TDLS_UAPSD_BUFFER_STA,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TDLS_UAPSD_BUFFER_STA;

		if (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TX_DATA_ACK_RSSI;

		if (test_bit(WMI_SERVICE_REPORT_AIRTIME, ar->wmi.svc_map))
			val |= WMI_10_4_REPORT_AIRTIME;

		status = ath10k_mac_ext_resource_config(ar, val);
		if (status) {
			ath10k_err(ar,
				   "failed to send ext resource cfg command : %d\n",
				   status);
			goto err_hif_stop;
		}
	}

	status = ath10k_wmi_cmd_init(ar);
	if (status) {
		ath10k_err(ar, "could not send WMI init command (%d)\n",
			   status);
		goto err_hif_stop;
	}

	status = ath10k_wmi_wait_for_unified_ready(ar);
	if (status) {
		ath10k_err(ar, "wmi unified ready event not received\n");
		goto err_hif_stop;
	}

	status = ath10k_core_compat_services(ar);
	if (status) {
		ath10k_err(ar, "compat services failed: %d\n", status);
		goto err_hif_stop;
	}

	status = ath10k_wmi_pdev_set_base_macaddr(ar, ar->mac_addr);
	if (status && status != -EOPNOTSUPP) {
		ath10k_err(ar,
			   "failed to set base mac address: %d\n", status);
		goto err_hif_stop;
	}

	/* Some firmware revisions do not properly set up hardware rx filter
	 * registers.
	 *
	 * A known example from QCA9880 and 10.2.4 is that MAC_PCU_ADDR1_MASK
	 * is filled with 0s instead of 1s allowing HW to respond with ACKs to
	 * any frames that matches MAC_PCU_RX_FILTER which is also
	 * misconfigured to accept anything.
	 *
	 * The ADDR1 is programmed using internal firmware structure field and
	 * can't be (easily/sanely) reached from the driver explicitly. It is
	 * possible to implicitly make it correct by creating a dummy vdev and
	 * then deleting it.
	 */
	if (ar->hw_params.hw_filter_reset_required &&
	    mode == ATH10K_FIRMWARE_MODE_NORMAL) {
		status = ath10k_core_reset_rx_filter(ar);
		if (status) {
			ath10k_err(ar,
				   "failed to reset rx filter: %d\n", status);
			goto err_hif_stop;
		}
	}

	status = ath10k_htt_rx_ring_refill(ar);
	if (status) {
		ath10k_err(ar, "failed to refill htt rx ring: %d\n", status);
		goto err_hif_stop;
	}

	if (ar->max_num_vdevs >= 64)
		ar->free_vdev_map = 0xFFFFFFFFFFFFFFFFLL;
	else
		ar->free_vdev_map = (1LL << ar->max_num_vdevs) - 1;

	INIT_LIST_HEAD(&ar->arvifs);

	/* we don't care about HTT in UTF mode */
	if (mode == ATH10K_FIRMWARE_MODE_NORMAL) {
		status = ath10k_htt_setup(&ar->htt);
		if (status) {
			ath10k_err(ar, "failed to setup htt: %d\n", status);
			goto err_hif_stop;
		}
	}

	status = ath10k_debug_start(ar);
	if (status)
		goto err_hif_stop;

	status = ath10k_hif_set_target_log_mode(ar, fw_diag_log);
	if (status && status != -EOPNOTSUPP) {
		ath10k_warn(ar, "set traget log mode faileds: %d\n", status);
		goto err_hif_stop;
	}

	return 0;

err_hif_stop:
	ath10k_hif_stop(ar);
err_htt_rx_detach:
	ath10k_htt_rx_free(&ar->htt);
err_htt_tx_detach:
	ath10k_htt_tx_free(&ar->htt);
err_wmi_detach:
	ath10k_wmi_detach(ar);
err:
	return status;
}
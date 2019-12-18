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
struct ath10k_fw_stats_vdev {int /*<<< orphan*/ * beacon_rssi_history; int /*<<< orphan*/ * tx_rate_history; int /*<<< orphan*/ * num_tx_frames_failures; int /*<<< orphan*/ * num_tx_frames_retries; int /*<<< orphan*/ * num_tx_frames; int /*<<< orphan*/  num_tx_not_acked; int /*<<< orphan*/  num_rx_discard; int /*<<< orphan*/  num_rx_err; int /*<<< orphan*/  num_rts_success; int /*<<< orphan*/  num_rts_fail; int /*<<< orphan*/  num_rx_frames; int /*<<< orphan*/  data_snr; int /*<<< orphan*/  beacon_snr; int /*<<< orphan*/  vdev_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ATH10K_FW_STATS_BUF_SIZE ; 
 int scnprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
ath10k_wmi_fw_vdev_stats_fill(const struct ath10k_fw_stats_vdev *vdev,
			      char *buf, u32 *length)
{
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;
	int i;

	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"vdev id", vdev->vdev_id);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"beacon snr", vdev->beacon_snr);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"data snr", vdev->data_snr);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num rx frames", vdev->num_rx_frames);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num rts fail", vdev->num_rts_fail);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num rts success", vdev->num_rts_success);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num rx err", vdev->num_rx_err);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num rx discard", vdev->num_rx_discard);
	len += scnprintf(buf + len, buf_len - len, "%30s %u\n",
			"num tx not acked", vdev->num_tx_not_acked);

	for (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames); i++)
		len += scnprintf(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames", i,
				vdev->num_tx_frames[i]);

	for (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_retries); i++)
		len += scnprintf(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames retries", i,
				vdev->num_tx_frames_retries[i]);

	for (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_failures); i++)
		len += scnprintf(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames failures", i,
				vdev->num_tx_frames_failures[i]);

	for (i = 0 ; i < ARRAY_SIZE(vdev->tx_rate_history); i++)
		len += scnprintf(buf + len, buf_len - len,
				"%25s [%02d] 0x%08x\n",
				"tx rate history", i,
				vdev->tx_rate_history[i]);

	for (i = 0 ; i < ARRAY_SIZE(vdev->beacon_rssi_history); i++)
		len += scnprintf(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"beacon rssi history", i,
				vdev->beacon_rssi_history[i]);

	len += scnprintf(buf + len, buf_len - len, "\n");
	*length = len;
}
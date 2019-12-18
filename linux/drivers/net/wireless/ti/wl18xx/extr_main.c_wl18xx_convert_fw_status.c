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
struct TYPE_3__ {int /*<<< orphan*/  hlid; int /*<<< orphan*/  tx_last_rate_mbps; int /*<<< orphan*/  tx_last_rate; int /*<<< orphan*/  tx_voice_released_blks; int /*<<< orphan*/  tx_lnk_free_pkts; int /*<<< orphan*/  tx_released_pkts; } ;
struct wl_fw_status {int /*<<< orphan*/ * priv; void* log_start_addr; TYPE_1__ counters; void* tx_total; void* total_released_blks; void* link_fast_bitmap; void* link_ps_bitmap; void* fw_localtime; int /*<<< orphan*/  rx_pkt_descs; int /*<<< orphan*/  tx_results_counter; int /*<<< orphan*/  drv_rx_counter; int /*<<< orphan*/  fw_rx_counter; void* intr; } ;
struct TYPE_4__ {int /*<<< orphan*/  hlid; int /*<<< orphan*/  tx_last_rate_mbps; int /*<<< orphan*/  tx_last_rate; int /*<<< orphan*/  tx_voice_released_blks; int /*<<< orphan*/  tx_lnk_free_pkts; int /*<<< orphan*/  tx_released_pkts; } ;
struct wl18xx_fw_status {int /*<<< orphan*/  priv; int /*<<< orphan*/  log_start_addr; TYPE_2__ counters; int /*<<< orphan*/  tx_total; int /*<<< orphan*/  total_released_blks; int /*<<< orphan*/  link_fast_bitmap; int /*<<< orphan*/  link_ps_bitmap; int /*<<< orphan*/  fw_localtime; int /*<<< orphan*/  rx_pkt_descs; int /*<<< orphan*/  tx_results_counter; int /*<<< orphan*/  drv_rx_counter; int /*<<< orphan*/  fw_rx_counter; int /*<<< orphan*/  intr; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl18xx_convert_fw_status(struct wl1271 *wl, void *raw_fw_status,
				     struct wl_fw_status *fw_status)
{
	struct wl18xx_fw_status *int_fw_status = raw_fw_status;

	fw_status->intr = le32_to_cpu(int_fw_status->intr);
	fw_status->fw_rx_counter = int_fw_status->fw_rx_counter;
	fw_status->drv_rx_counter = int_fw_status->drv_rx_counter;
	fw_status->tx_results_counter = int_fw_status->tx_results_counter;
	fw_status->rx_pkt_descs = int_fw_status->rx_pkt_descs;

	fw_status->fw_localtime = le32_to_cpu(int_fw_status->fw_localtime);
	fw_status->link_ps_bitmap = le32_to_cpu(int_fw_status->link_ps_bitmap);
	fw_status->link_fast_bitmap =
			le32_to_cpu(int_fw_status->link_fast_bitmap);
	fw_status->total_released_blks =
			le32_to_cpu(int_fw_status->total_released_blks);
	fw_status->tx_total = le32_to_cpu(int_fw_status->tx_total);

	fw_status->counters.tx_released_pkts =
			int_fw_status->counters.tx_released_pkts;
	fw_status->counters.tx_lnk_free_pkts =
			int_fw_status->counters.tx_lnk_free_pkts;
	fw_status->counters.tx_voice_released_blks =
			int_fw_status->counters.tx_voice_released_blks;
	fw_status->counters.tx_last_rate =
			int_fw_status->counters.tx_last_rate;
	fw_status->counters.tx_last_rate_mbps =
			int_fw_status->counters.tx_last_rate_mbps;
	fw_status->counters.hlid =
			int_fw_status->counters.hlid;

	fw_status->log_start_addr = le32_to_cpu(int_fw_status->log_start_addr);

	fw_status->priv = &int_fw_status->priv;
}
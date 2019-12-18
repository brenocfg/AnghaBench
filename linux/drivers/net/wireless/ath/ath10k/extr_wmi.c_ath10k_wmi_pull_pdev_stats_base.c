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
struct wmi_pdev_stats_base {int /*<<< orphan*/  chan_tx_pwr; int /*<<< orphan*/  phy_err_count; int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  rx_clear_count; int /*<<< orphan*/  rx_frame_count; int /*<<< orphan*/  tx_frame_count; int /*<<< orphan*/  chan_nf; } ;
struct ath10k_fw_stats_pdev {void* chan_tx_power; void* phy_err_count; void* cycle_count; void* rx_clear_count; void* rx_frame_count; void* tx_frame_count; void* ch_noise_floor; } ;

/* Variables and functions */
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

void ath10k_wmi_pull_pdev_stats_base(const struct wmi_pdev_stats_base *src,
				     struct ath10k_fw_stats_pdev *dst)
{
	dst->ch_noise_floor = __le32_to_cpu(src->chan_nf);
	dst->tx_frame_count = __le32_to_cpu(src->tx_frame_count);
	dst->rx_frame_count = __le32_to_cpu(src->rx_frame_count);
	dst->rx_clear_count = __le32_to_cpu(src->rx_clear_count);
	dst->cycle_count = __le32_to_cpu(src->cycle_count);
	dst->phy_err_count = __le32_to_cpu(src->phy_err_count);
	dst->chan_tx_power = __le32_to_cpu(src->chan_tx_pwr);
}
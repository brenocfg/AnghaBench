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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_10_4_peer_stats {int /*<<< orphan*/  peer_rx_rate; int /*<<< orphan*/  peer_tx_rate; int /*<<< orphan*/  peer_rssi; TYPE_1__ peer_macaddr; } ;
struct ath10k_fw_stats_peer {void* peer_rx_rate; void* peer_tx_rate; void* peer_rssi; int /*<<< orphan*/  peer_macaddr; } ;

/* Variables and functions */
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_wmi_10_4_pull_peer_stats(const struct wmi_10_4_peer_stats *src,
				struct ath10k_fw_stats_peer *dst)
{
	ether_addr_copy(dst->peer_macaddr, src->peer_macaddr.addr);
	dst->peer_rssi = __le32_to_cpu(src->peer_rssi);
	dst->peer_tx_rate = __le32_to_cpu(src->peer_tx_rate);
	dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);
}
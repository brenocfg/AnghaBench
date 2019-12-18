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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  failure_frame; int /*<<< orphan*/  rate_n_flags; TYPE_1__ status; } ;
struct iwlagn_beacon_notif {int /*<<< orphan*/  ibss_mgr_status; int /*<<< orphan*/  low_tsf; int /*<<< orphan*/  high_tsf; TYPE_2__ beacon_notify_hdr; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  ibss_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_priv*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TX_STATUS_MSK ; 
 int /*<<< orphan*/  iwl_hw_get_rate (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwlagn_rx_beacon_notif(struct iwl_priv *priv,
				   struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwlagn_beacon_notif *beacon = (void *)pkt->data;
#ifdef CONFIG_IWLWIFI_DEBUG
	u16 status = le16_to_cpu(beacon->beacon_notify_hdr.status.status);
	u8 rate = iwl_hw_get_rate(beacon->beacon_notify_hdr.rate_n_flags);

	IWL_DEBUG_RX(priv, "beacon status %#x, retries:%d ibssmgr:%d "
		"tsf:0x%.8x%.8x rate:%d\n",
		status & TX_STATUS_MSK,
		beacon->beacon_notify_hdr.failure_frame,
		le32_to_cpu(beacon->ibss_mgr_status),
		le32_to_cpu(beacon->high_tsf),
		le32_to_cpu(beacon->low_tsf), rate);
#endif

	priv->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);
}
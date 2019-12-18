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
struct wil_net_stats {int /*<<< orphan*/  rx_amsdu_error; int /*<<< orphan*/  rx_replay; int /*<<< orphan*/  rx_key_error; int /*<<< orphan*/  rx_mic_error; } ;
struct wil6210_priv {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int EFAULT ; 
 int WIL_RX_EDMA_ERROR_AMSDU ; 
 int WIL_RX_EDMA_ERROR_KEY ; 
 int WIL_RX_EDMA_ERROR_MIC ; 
 int WIL_RX_EDMA_ERROR_REPLAY ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_err_ratelimited (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_rx_status_get_checksum (void*,struct wil_net_stats*) ; 
 int wil_rx_status_get_l2_rx_status (void*) ; 
 void* wil_skb_rxstatus (struct sk_buff*) ; 

__attribute__((used)) static int wil_rx_error_check_edma(struct wil6210_priv *wil,
				   struct sk_buff *skb,
				   struct wil_net_stats *stats)
{
	int l2_rx_status;
	void *msg = wil_skb_rxstatus(skb);

	l2_rx_status = wil_rx_status_get_l2_rx_status(msg);
	if (l2_rx_status != 0) {
		wil_dbg_txrx(wil, "L2 RX error, l2_rx_status=0x%x\n",
			     l2_rx_status);
		/* Due to HW issue, KEY error will trigger a MIC error */
		if (l2_rx_status == WIL_RX_EDMA_ERROR_MIC) {
			wil_err_ratelimited(wil,
					    "L2 MIC/KEY error, dropping packet\n");
			stats->rx_mic_error++;
		}
		if (l2_rx_status == WIL_RX_EDMA_ERROR_KEY) {
			wil_err_ratelimited(wil,
					    "L2 KEY error, dropping packet\n");
			stats->rx_key_error++;
		}
		if (l2_rx_status == WIL_RX_EDMA_ERROR_REPLAY) {
			wil_err_ratelimited(wil,
					    "L2 REPLAY error, dropping packet\n");
			stats->rx_replay++;
		}
		if (l2_rx_status == WIL_RX_EDMA_ERROR_AMSDU) {
			wil_err_ratelimited(wil,
					    "L2 AMSDU error, dropping packet\n");
			stats->rx_amsdu_error++;
		}
		return -EFAULT;
	}

	skb->ip_summed = wil_rx_status_get_checksum(msg, stats);

	return 0;
}
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
typedef  enum ath10k_pkt_rx_err { ____Placeholder_ath10k_pkt_rx_err } ath10k_pkt_rx_err ;

/* Variables and functions */
#define  ATH10K_PKT_RX_ERR_CRYPT 132 
#define  ATH10K_PKT_RX_ERR_FCS 131 
#define  ATH10K_PKT_RX_ERR_MAX 130 
#define  ATH10K_PKT_RX_ERR_PEER_IDX_INVAL 129 
#define  ATH10K_PKT_RX_ERR_TKIP 128 

__attribute__((used)) static char *get_err_str(enum ath10k_pkt_rx_err i)
{
	switch (i) {
	case ATH10K_PKT_RX_ERR_FCS:
		return "fcs_err";
	case ATH10K_PKT_RX_ERR_TKIP:
		return "tkip_err";
	case ATH10K_PKT_RX_ERR_CRYPT:
		return "crypt_err";
	case ATH10K_PKT_RX_ERR_PEER_IDX_INVAL:
		return "peer_idx_inval";
	case ATH10K_PKT_RX_ERR_MAX:
		return "unknown";
	}

	return "unknown";
}
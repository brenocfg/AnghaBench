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
struct bna_tx {int dummy; } ;
struct bna_rx {int /*<<< orphan*/  rxf; } ;
struct bna {int /*<<< orphan*/  tx_mod; int /*<<< orphan*/  ethport; int /*<<< orphan*/  ioceth; int /*<<< orphan*/  enet; } ;
struct bfi_msgq_mhdr {int msg_id; int /*<<< orphan*/  enet_id; } ;

/* Variables and functions */
#define  BFI_ENET_I2H_BW_UPDATE_AEN 156 
#define  BFI_ENET_I2H_DIAG_LOOPBACK_RSP 155 
#define  BFI_ENET_I2H_GET_ATTR_RSP 154 
#define  BFI_ENET_I2H_LINK_DOWN_AEN 153 
#define  BFI_ENET_I2H_LINK_UP_AEN 152 
#define  BFI_ENET_I2H_MAC_MCAST_ADD_RSP 151 
#define  BFI_ENET_I2H_MAC_MCAST_DEL_RSP 150 
#define  BFI_ENET_I2H_MAC_MCAST_FILTER_RSP 149 
#define  BFI_ENET_I2H_MAC_UCAST_ADD_RSP 148 
#define  BFI_ENET_I2H_MAC_UCAST_CLR_RSP 147 
#define  BFI_ENET_I2H_MAC_UCAST_DEL_RSP 146 
#define  BFI_ENET_I2H_MAC_UCAST_SET_RSP 145 
#define  BFI_ENET_I2H_PORT_ADMIN_RSP 144 
#define  BFI_ENET_I2H_PORT_DISABLE_AEN 143 
#define  BFI_ENET_I2H_PORT_ENABLE_AEN 142 
#define  BFI_ENET_I2H_RIT_CFG_RSP 141 
#define  BFI_ENET_I2H_RSS_CFG_RSP 140 
#define  BFI_ENET_I2H_RSS_ENABLE_RSP 139 
#define  BFI_ENET_I2H_RX_CFG_CLR_RSP 138 
#define  BFI_ENET_I2H_RX_CFG_SET_RSP 137 
#define  BFI_ENET_I2H_RX_DEFAULT_RSP 136 
#define  BFI_ENET_I2H_RX_PROMISCUOUS_RSP 135 
#define  BFI_ENET_I2H_RX_VLAN_SET_RSP 134 
#define  BFI_ENET_I2H_RX_VLAN_STRIP_ENABLE_RSP 133 
#define  BFI_ENET_I2H_SET_PAUSE_RSP 132 
#define  BFI_ENET_I2H_STATS_CLR_RSP 131 
#define  BFI_ENET_I2H_STATS_GET_RSP 130 
#define  BFI_ENET_I2H_TX_CFG_CLR_RSP 129 
#define  BFI_ENET_I2H_TX_CFG_SET_RSP 128 
 int /*<<< orphan*/  bna_bfi_attr_get_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_bw_update_aen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_bfi_ethport_admin_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_disable_aen (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_enable_aen (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_linkdown_aen (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_linkup_aen (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_lpbk_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_pause_set_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_rx_enet_start_rsp (struct bna_rx*,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_rx_enet_stop_rsp (struct bna_rx*,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_rxf_cfg_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_rxf_mcast_add_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_rxf_ucast_set_rsp (int /*<<< orphan*/ *,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_stats_get_rsp (struct bna*,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_tx_enet_start_rsp (struct bna_tx*,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_bfi_tx_enet_stop_rsp (struct bna_tx*,struct bfi_msgq_mhdr*) ; 
 int /*<<< orphan*/  bna_rx_from_rid (struct bna*,int /*<<< orphan*/ ,struct bna_rx*) ; 
 int /*<<< orphan*/  bna_tx_from_rid (struct bna*,int /*<<< orphan*/ ,struct bna_tx*) ; 

__attribute__((used)) static void
bna_msgq_rsp_handler(void *arg, struct bfi_msgq_mhdr *msghdr)
{
	struct bna *bna = (struct bna *)arg;
	struct bna_tx *tx;
	struct bna_rx *rx;

	switch (msghdr->msg_id) {
	case BFI_ENET_I2H_RX_CFG_SET_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		if (rx)
			bna_bfi_rx_enet_start_rsp(rx, msghdr);
		break;

	case BFI_ENET_I2H_RX_CFG_CLR_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		if (rx)
			bna_bfi_rx_enet_stop_rsp(rx, msghdr);
		break;

	case BFI_ENET_I2H_RIT_CFG_RSP:
	case BFI_ENET_I2H_RSS_CFG_RSP:
	case BFI_ENET_I2H_RSS_ENABLE_RSP:
	case BFI_ENET_I2H_RX_PROMISCUOUS_RSP:
	case BFI_ENET_I2H_RX_DEFAULT_RSP:
	case BFI_ENET_I2H_MAC_UCAST_CLR_RSP:
	case BFI_ENET_I2H_MAC_UCAST_ADD_RSP:
	case BFI_ENET_I2H_MAC_UCAST_DEL_RSP:
	case BFI_ENET_I2H_MAC_MCAST_DEL_RSP:
	case BFI_ENET_I2H_MAC_MCAST_FILTER_RSP:
	case BFI_ENET_I2H_RX_VLAN_SET_RSP:
	case BFI_ENET_I2H_RX_VLAN_STRIP_ENABLE_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		if (rx)
			bna_bfi_rxf_cfg_rsp(&rx->rxf, msghdr);
		break;

	case BFI_ENET_I2H_MAC_UCAST_SET_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		if (rx)
			bna_bfi_rxf_ucast_set_rsp(&rx->rxf, msghdr);
		break;

	case BFI_ENET_I2H_MAC_MCAST_ADD_RSP:
		bna_rx_from_rid(bna, msghdr->enet_id, rx);
		if (rx)
			bna_bfi_rxf_mcast_add_rsp(&rx->rxf, msghdr);
		break;

	case BFI_ENET_I2H_TX_CFG_SET_RSP:
		bna_tx_from_rid(bna, msghdr->enet_id, tx);
		if (tx)
			bna_bfi_tx_enet_start_rsp(tx, msghdr);
		break;

	case BFI_ENET_I2H_TX_CFG_CLR_RSP:
		bna_tx_from_rid(bna, msghdr->enet_id, tx);
		if (tx)
			bna_bfi_tx_enet_stop_rsp(tx, msghdr);
		break;

	case BFI_ENET_I2H_PORT_ADMIN_RSP:
		bna_bfi_ethport_admin_rsp(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_DIAG_LOOPBACK_RSP:
		bna_bfi_ethport_lpbk_rsp(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_SET_PAUSE_RSP:
		bna_bfi_pause_set_rsp(&bna->enet, msghdr);
		break;

	case BFI_ENET_I2H_GET_ATTR_RSP:
		bna_bfi_attr_get_rsp(&bna->ioceth, msghdr);
		break;

	case BFI_ENET_I2H_STATS_GET_RSP:
		bna_bfi_stats_get_rsp(bna, msghdr);
		break;

	case BFI_ENET_I2H_STATS_CLR_RSP:
		/* No-op */
		break;

	case BFI_ENET_I2H_LINK_UP_AEN:
		bna_bfi_ethport_linkup_aen(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_LINK_DOWN_AEN:
		bna_bfi_ethport_linkdown_aen(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_PORT_ENABLE_AEN:
		bna_bfi_ethport_enable_aen(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_PORT_DISABLE_AEN:
		bna_bfi_ethport_disable_aen(&bna->ethport, msghdr);
		break;

	case BFI_ENET_I2H_BW_UPDATE_AEN:
		bna_bfi_bw_update_aen(&bna->tx_mod);
		break;

	default:
		break;
	}
}
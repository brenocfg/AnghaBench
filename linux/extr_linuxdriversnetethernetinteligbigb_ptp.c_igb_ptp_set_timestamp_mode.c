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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ETQF (int /*<<< orphan*/ ) ; 
 int E1000_ETQF_1588 ; 
 int E1000_ETQF_FILTER_ENABLE ; 
 int /*<<< orphan*/  E1000_FTQF (int) ; 
 int E1000_FTQF_1588_TIME_STAMP ; 
 int E1000_FTQF_MASK ; 
 int E1000_FTQF_MASK_PROTO_BP ; 
 int E1000_FTQF_MASK_SOURCE_PORT_BP ; 
 int E1000_FTQF_VF_BP ; 
 int /*<<< orphan*/  E1000_IMIR (int) ; 
 int /*<<< orphan*/  E1000_IMIREXT (int) ; 
 int E1000_IMIREXT_CTRL_BP ; 
 int E1000_IMIREXT_SIZE_BP ; 
 int /*<<< orphan*/  E1000_RXPBS ; 
 int E1000_RXPBS_CFG_TS_EN ; 
 int /*<<< orphan*/  E1000_RXSTMPH ; 
 int /*<<< orphan*/  E1000_RXSTMPL ; 
 int /*<<< orphan*/  E1000_SPQF (int) ; 
 int /*<<< orphan*/  E1000_TSYNCRXCFG ; 
 int E1000_TSYNCRXCFG_PTP_V1_DELAY_REQ_MESSAGE ; 
 int E1000_TSYNCRXCFG_PTP_V1_SYNC_MESSAGE ; 
 int /*<<< orphan*/  E1000_TSYNCRXCTL ; 
 int E1000_TSYNCRXCTL_ENABLED ; 
 int E1000_TSYNCRXCTL_TYPE_ALL ; 
 int E1000_TSYNCRXCTL_TYPE_EVENT_V2 ; 
 int E1000_TSYNCRXCTL_TYPE_L4_V1 ; 
 int E1000_TSYNCRXCTL_TYPE_MASK ; 
 int /*<<< orphan*/  E1000_TSYNCTXCTL ; 
 int E1000_TSYNCTXCTL_ENABLED ; 
 int /*<<< orphan*/  E1000_TXSTMPH ; 
 int /*<<< orphan*/  E1000_TXSTMPL ; 
 int EINVAL ; 
 int ERANGE ; 
 int ETH_P_1588 ; 
#define  HWTSTAMP_FILTER_ALL 144 
#define  HWTSTAMP_FILTER_NONE 143 
#define  HWTSTAMP_FILTER_NTP_ALL 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 141 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 140 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 139 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 133 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 131 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 int /*<<< orphan*/  IGB_ETQF_FILTER_1588 ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  PTP_EV_PORT ; 
 scalar_t__ e1000_82575 ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_82580 ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_i211 ; 
 int htons (int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static int igb_ptp_set_timestamp_mode(struct igb_adapter *adapter,
				      struct hwtstamp_config *config)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = E1000_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
	u32 tsync_rx_cfg = 0;
	bool is_l4 = false;
	bool is_l2 = false;
	u32 regval;

	/* reserved for future extensions */
	if (config->flags)
		return -EINVAL;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
	case HWTSTAMP_TX_ON:
		break;
	default:
		return -ERANGE;
	}

	switch (config->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		tsync_rx_ctl = 0;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_cfg = E1000_TSYNCRXCFG_PTP_V1_SYNC_MESSAGE;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_cfg = E1000_TSYNCRXCFG_PTP_V1_DELAY_REQ_MESSAGE;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_EVENT_V2;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		is_l2 = true;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_NTP_ALL:
	case HWTSTAMP_FILTER_ALL:
		/* 82576 cannot timestamp all packets, which it needs to do to
		 * support both V1 Sync and Delay_Req messages
		 */
		if (hw->mac.type != e1000_82576) {
			tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
			config->rx_filter = HWTSTAMP_FILTER_ALL;
			break;
		}
		/* fall through */
	default:
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		return -ERANGE;
	}

	if (hw->mac.type == e1000_82575) {
		if (tsync_rx_ctl | tsync_tx_ctl)
			return -EINVAL;
		return 0;
	}

	/* Per-packet timestamping only works if all packets are
	 * timestamped, so enable timestamping in all packets as
	 * long as one Rx filter was configured.
	 */
	if ((hw->mac.type >= e1000_82580) && tsync_rx_ctl) {
		tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		is_l2 = true;
		is_l4 = true;

		if ((hw->mac.type == e1000_i210) ||
		    (hw->mac.type == e1000_i211)) {
			regval = rd32(E1000_RXPBS);
			regval |= E1000_RXPBS_CFG_TS_EN;
			wr32(E1000_RXPBS, regval);
		}
	}

	/* enable/disable TX */
	regval = rd32(E1000_TSYNCTXCTL);
	regval &= ~E1000_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	wr32(E1000_TSYNCTXCTL, regval);

	/* enable/disable RX */
	regval = rd32(E1000_TSYNCRXCTL);
	regval &= ~(E1000_TSYNCRXCTL_ENABLED | E1000_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	wr32(E1000_TSYNCRXCTL, regval);

	/* define which PTP packets are time stamped */
	wr32(E1000_TSYNCRXCFG, tsync_rx_cfg);

	/* define ethertype filter for timestamped packets */
	if (is_l2)
		wr32(E1000_ETQF(IGB_ETQF_FILTER_1588),
		     (E1000_ETQF_FILTER_ENABLE | /* enable filter */
		      E1000_ETQF_1588 | /* enable timestamping */
		      ETH_P_1588));     /* 1588 eth protocol type */
	else
		wr32(E1000_ETQF(IGB_ETQF_FILTER_1588), 0);

	/* L4 Queue Filter[3]: filter by destination port and protocol */
	if (is_l4) {
		u32 ftqf = (IPPROTO_UDP /* UDP */
			| E1000_FTQF_VF_BP /* VF not compared */
			| E1000_FTQF_1588_TIME_STAMP /* Enable Timestamping */
			| E1000_FTQF_MASK); /* mask all inputs */
		ftqf &= ~E1000_FTQF_MASK_PROTO_BP; /* enable protocol check */

		wr32(E1000_IMIR(3), htons(PTP_EV_PORT));
		wr32(E1000_IMIREXT(3),
		     (E1000_IMIREXT_SIZE_BP | E1000_IMIREXT_CTRL_BP));
		if (hw->mac.type == e1000_82576) {
			/* enable source port check */
			wr32(E1000_SPQF(3), htons(PTP_EV_PORT));
			ftqf &= ~E1000_FTQF_MASK_SOURCE_PORT_BP;
		}
		wr32(E1000_FTQF(3), ftqf);
	} else {
		wr32(E1000_FTQF(3), E1000_FTQF_MASK);
	}
	wrfl();

	/* clear TX/RX time stamp registers, just to be sure */
	regval = rd32(E1000_TXSTMPL);
	regval = rd32(E1000_TXSTMPH);
	regval = rd32(E1000_RXSTMPL);
	regval = rd32(E1000_RXSTMPH);

	return 0;
}
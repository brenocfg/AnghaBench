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
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; struct ixgbe_hw hw; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int ETH_P_1588 ; 
#define  HWTSTAMP_FILTER_ALL 147 
#define  HWTSTAMP_FILTER_NONE 146 
#define  HWTSTAMP_FILTER_NTP_ALL 145 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 144 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 142 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 141 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 140 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 137 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 134 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 133 
#define  HWTSTAMP_TX_OFF 132 
#define  HWTSTAMP_TX_ON 131 
 int /*<<< orphan*/  IXGBE_ETQF (int /*<<< orphan*/ ) ; 
 int IXGBE_ETQF_1588 ; 
 int /*<<< orphan*/  IXGBE_ETQF_FILTER_1588 ; 
 int IXGBE_ETQF_FILTER_EN ; 
 int IXGBE_FLAG_RX_HWTSTAMP_ENABLED ; 
 int IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXMTRL ; 
 int IXGBE_RXMTRL_V1_DELAY_REQ_MSG ; 
 int IXGBE_RXMTRL_V1_SYNC_MSG ; 
 int /*<<< orphan*/  IXGBE_RXSTMPH ; 
 int /*<<< orphan*/  IXGBE_TSYNCRXCTL ; 
 int IXGBE_TSYNCRXCTL_ENABLED ; 
 int IXGBE_TSYNCRXCTL_TSIP_UT_EN ; 
 int IXGBE_TSYNCRXCTL_TYPE_ALL ; 
 int IXGBE_TSYNCRXCTL_TYPE_EVENT_V2 ; 
 int IXGBE_TSYNCRXCTL_TYPE_L4_V1 ; 
 int IXGBE_TSYNCRXCTL_TYPE_MASK ; 
 int /*<<< orphan*/  IXGBE_TSYNCTXCTL ; 
 int IXGBE_TSYNCTXCTL_ENABLED ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int PTP_EV_PORT ; 
 int ixgbe_mac_82598EB ; 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  ixgbe_ptp_clear_tx_timestamp (struct ixgbe_adapter*) ; 

__attribute__((used)) static int ixgbe_ptp_set_timestamp_mode(struct ixgbe_adapter *adapter,
				 struct hwtstamp_config *config)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = IXGBE_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = IXGBE_TSYNCRXCTL_ENABLED;
	u32 tsync_rx_mtrl = PTP_EV_PORT << 16;
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
		tsync_rx_mtrl = 0;
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_SYNC_MSG;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_DELAY_REQ_MSG;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
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
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_EVENT_V2;
		is_l2 = true;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		adapter->flags |= (IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				   IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_NTP_ALL:
	case HWTSTAMP_FILTER_ALL:
		/* The X550 controller is capable of timestamping all packets,
		 * which allows it to accept any filter.
		 */
		if (hw->mac.type >= ixgbe_mac_X550) {
			tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_ALL;
			config->rx_filter = HWTSTAMP_FILTER_ALL;
			adapter->flags |= IXGBE_FLAG_RX_HWTSTAMP_ENABLED;
			break;
		}
		/* fall through */
	default:
		/*
		 * register RXMTRL must be set in order to do V1 packets,
		 * therefore it is not possible to time stamp both V1 Sync and
		 * Delay_Req messages and hardware does not support
		 * timestamping all packets => return error
		 */
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		return -ERANGE;
	}

	if (hw->mac.type == ixgbe_mac_82598EB) {
		adapter->flags &= ~(IXGBE_FLAG_RX_HWTSTAMP_ENABLED |
				    IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER);
		if (tsync_rx_ctl | tsync_tx_ctl)
			return -ERANGE;
		return 0;
	}

	/* Per-packet timestamping only works if the filter is set to all
	 * packets. Since this is desired, always timestamp all packets as long
	 * as any Rx filter was configured.
	 */
	switch (hw->mac.type) {
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		/* enable timestamping all packets only if at least some
		 * packets were requested. Otherwise, play nice and disable
		 * timestamping
		 */
		if (config->rx_filter == HWTSTAMP_FILTER_NONE)
			break;

		tsync_rx_ctl = IXGBE_TSYNCRXCTL_ENABLED |
			       IXGBE_TSYNCRXCTL_TYPE_ALL |
			       IXGBE_TSYNCRXCTL_TSIP_UT_EN;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		adapter->flags |= IXGBE_FLAG_RX_HWTSTAMP_ENABLED;
		adapter->flags &= ~IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER;
		is_l2 = true;
		break;
	default:
		break;
	}

	/* define ethertype filter for timestamping L2 packets */
	if (is_l2)
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588),
				(IXGBE_ETQF_FILTER_EN | /* enable filter */
				 IXGBE_ETQF_1588 | /* enable timestamping */
				 ETH_P_1588));     /* 1588 eth protocol type */
	else
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588), 0);

	/* enable/disable TX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCTXCTL);
	regval &= ~IXGBE_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCTXCTL, regval);

	/* enable/disable RX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	regval &= ~(IXGBE_TSYNCRXCTL_ENABLED | IXGBE_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCRXCTL, regval);

	/* define which PTP packets are time stamped */
	IXGBE_WRITE_REG(hw, IXGBE_RXMTRL, tsync_rx_mtrl);

	IXGBE_WRITE_FLUSH(hw);

	/* clear TX/RX time stamp registers, just to be sure */
	ixgbe_ptp_clear_tx_timestamp(adapter);
	IXGBE_READ_REG(hw, IXGBE_RXSTMPH);

	return 0;
}
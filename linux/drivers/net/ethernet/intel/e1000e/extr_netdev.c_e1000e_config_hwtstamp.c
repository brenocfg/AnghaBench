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
typedef  int u16 ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags; struct hwtstamp_config hwtstamp_config; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RXMTRL_PTP_V1_DELAY_REQ_MESSAGE ; 
 int E1000_RXMTRL_PTP_V1_SYNC_MESSAGE ; 
 int E1000_RXMTRL_PTP_V2_DELAY_REQ_MESSAGE ; 
 int E1000_RXMTRL_PTP_V2_SYNC_MESSAGE ; 
 int E1000_TSYNCRXCTL_ENABLED ; 
 int E1000_TSYNCRXCTL_TYPE_ALL ; 
 int E1000_TSYNCRXCTL_TYPE_EVENT_V2 ; 
 int E1000_TSYNCRXCTL_TYPE_L2_L4_V2 ; 
 int E1000_TSYNCRXCTL_TYPE_L2_V2 ; 
 int E1000_TSYNCRXCTL_TYPE_L4_V1 ; 
 int E1000_TSYNCRXCTL_TYPE_MASK ; 
 int E1000_TSYNCTXCTL_ENABLED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ERANGE ; 
 int ETH_P_1588 ; 
 int FLAG_HAS_HW_TIMESTAMP ; 
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
 int PTP_EV_PORT ; 
 int /*<<< orphan*/  RXMTRL ; 
 int /*<<< orphan*/  RXSTMPH ; 
 int /*<<< orphan*/  RXUDP ; 
 int /*<<< orphan*/  TSYNCRXCTL ; 
 int /*<<< orphan*/  TSYNCTXCTL ; 
 int /*<<< orphan*/  TXSTMPH ; 
 int /*<<< orphan*/  cpu_to_be16s (int*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int e1000e_config_hwtstamp(struct e1000_adapter *adapter,
				  struct hwtstamp_config *config)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = E1000_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
	u32 rxmtrl = 0;
	u16 rxudp = 0;
	bool is_l4 = false;
	bool is_l2 = false;
	u32 regval;

	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		return -EINVAL;

	/* flags reserved for future extensions - must be zero */
	if (config->flags)
		return -EINVAL;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
		break;
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
		rxmtrl = E1000_RXMTRL_PTP_V1_SYNC_MESSAGE;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		rxmtrl = E1000_RXMTRL_PTP_V1_DELAY_REQ_MESSAGE;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
		/* Also time stamps V2 L2 Path Delay Request/Response */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_SYNC_MESSAGE;
		is_l2 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		/* Also time stamps V2 L2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_DELAY_REQ_MESSAGE;
		is_l2 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
		/* Hardware cannot filter just V2 L4 Sync messages;
		 * fall-through to V2 (both L2 and L4) Sync.
		 */
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
		/* Also time stamps V2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_L4_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_SYNC_MESSAGE;
		is_l2 = true;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		/* Hardware cannot filter just V2 L4 Delay Request messages;
		 * fall-through to V2 (both L2 and L4) Delay Request.
		 */
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		/* Also time stamps V2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_L4_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_DELAY_REQ_MESSAGE;
		is_l2 = true;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		/* Hardware cannot filter just V2 L4 or L2 Event messages;
		 * fall-through to all V2 (both L2 and L4) Events.
		 */
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_EVENT_V2;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		is_l2 = true;
		is_l4 = true;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		/* For V1, the hardware can only filter Sync messages or
		 * Delay Request messages but not both so fall-through to
		 * time stamp all packets.
		 */
	case HWTSTAMP_FILTER_NTP_ALL:
	case HWTSTAMP_FILTER_ALL:
		is_l2 = true;
		is_l4 = true;
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		break;
	default:
		return -ERANGE;
	}

	adapter->hwtstamp_config = *config;

	/* enable/disable Tx h/w time stamping */
	regval = er32(TSYNCTXCTL);
	regval &= ~E1000_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	ew32(TSYNCTXCTL, regval);
	if ((er32(TSYNCTXCTL) & E1000_TSYNCTXCTL_ENABLED) !=
	    (regval & E1000_TSYNCTXCTL_ENABLED)) {
		e_err("Timesync Tx Control register not set as expected\n");
		return -EAGAIN;
	}

	/* enable/disable Rx h/w time stamping */
	regval = er32(TSYNCRXCTL);
	regval &= ~(E1000_TSYNCRXCTL_ENABLED | E1000_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	ew32(TSYNCRXCTL, regval);
	if ((er32(TSYNCRXCTL) & (E1000_TSYNCRXCTL_ENABLED |
				 E1000_TSYNCRXCTL_TYPE_MASK)) !=
	    (regval & (E1000_TSYNCRXCTL_ENABLED |
		       E1000_TSYNCRXCTL_TYPE_MASK))) {
		e_err("Timesync Rx Control register not set as expected\n");
		return -EAGAIN;
	}

	/* L2: define ethertype filter for time stamped packets */
	if (is_l2)
		rxmtrl |= ETH_P_1588;

	/* define which PTP packets get time stamped */
	ew32(RXMTRL, rxmtrl);

	/* Filter by destination port */
	if (is_l4) {
		rxudp = PTP_EV_PORT;
		cpu_to_be16s(&rxudp);
	}
	ew32(RXUDP, rxudp);

	e1e_flush();

	/* Clear TSYNCRXCTL_VALID & TSYNCTXCTL_VALID bit */
	er32(RXSTMPH);
	er32(TXSTMPH);

	return 0;
}
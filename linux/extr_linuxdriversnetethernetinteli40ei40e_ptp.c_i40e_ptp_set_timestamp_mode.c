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
struct i40e_hw {int dummy; } ;
struct i40e_pf {int ptp_tx; int ptp_rx; int hw_features; int /*<<< orphan*/  ptp_rx_lock; scalar_t__ latch_event_flags; struct i40e_hw hw; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
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
 int I40E_HW_PTP_L4_CAPABLE ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int I40E_PFINT_ICR0_ENA_TIMESYNC_MASK ; 
 int /*<<< orphan*/  I40E_PRTTSYN_CTL0 ; 
 int I40E_PRTTSYN_CTL0_TXTIME_INT_ENA_MASK ; 
 int /*<<< orphan*/  I40E_PRTTSYN_CTL1 ; 
 int I40E_PRTTSYN_CTL1_TSYNENA_MASK ; 
 int I40E_PRTTSYN_CTL1_TSYNTYPE_V1 ; 
 int I40E_PRTTSYN_CTL1_TSYNTYPE_V2 ; 
 int I40E_PRTTSYN_CTL1_UDP_ENA_MASK ; 
 int I40E_PRTTSYN_CTL1_V1MESSTYPE0_MASK ; 
 int I40E_PRTTSYN_CTL1_V2MESSTYPE0_MASK ; 
 int /*<<< orphan*/  I40E_PRTTSYN_RXTIME_H (int) ; 
 int /*<<< orphan*/  I40E_PRTTSYN_STAT_0 ; 
 int /*<<< orphan*/  I40E_PRTTSYN_TXTIME_H ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i40e_ptp_set_timestamp_mode(struct i40e_pf *pf,
				       struct hwtstamp_config *config)
{
	struct i40e_hw *hw = &pf->hw;
	u32 tsyntype, regval;

	/* Reserved for future extensions. */
	if (config->flags)
		return -EINVAL;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		pf->ptp_tx = false;
		break;
	case HWTSTAMP_TX_ON:
		pf->ptp_tx = true;
		break;
	default:
		return -ERANGE;
	}

	switch (config->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		pf->ptp_rx = false;
		/* We set the type to V1, but do not enable UDP packet
		 * recognition. In this way, we should be as close to
		 * disabling PTP Rx timestamps as possible since V1 packets
		 * are always UDP, since L2 packets are a V2 feature.
		 */
		tsyntype = I40E_PRTTSYN_CTL1_TSYNTYPE_V1;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		if (!(pf->hw_features & I40E_HW_PTP_L4_CAPABLE))
			return -ERANGE;
		pf->ptp_rx = true;
		tsyntype = I40E_PRTTSYN_CTL1_V1MESSTYPE0_MASK |
			   I40E_PRTTSYN_CTL1_TSYNTYPE_V1 |
			   I40E_PRTTSYN_CTL1_UDP_ENA_MASK;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		if (!(pf->hw_features & I40E_HW_PTP_L4_CAPABLE))
			return -ERANGE;
		/* fall through */
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		pf->ptp_rx = true;
		tsyntype = I40E_PRTTSYN_CTL1_V2MESSTYPE0_MASK |
			   I40E_PRTTSYN_CTL1_TSYNTYPE_V2;
		if (pf->hw_features & I40E_HW_PTP_L4_CAPABLE) {
			tsyntype |= I40E_PRTTSYN_CTL1_UDP_ENA_MASK;
			config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		} else {
			config->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		}
		break;
	case HWTSTAMP_FILTER_NTP_ALL:
	case HWTSTAMP_FILTER_ALL:
	default:
		return -ERANGE;
	}

	/* Clear out all 1588-related registers to clear and unlatch them. */
	spin_lock_bh(&pf->ptp_rx_lock);
	rd32(hw, I40E_PRTTSYN_STAT_0);
	rd32(hw, I40E_PRTTSYN_TXTIME_H);
	rd32(hw, I40E_PRTTSYN_RXTIME_H(0));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(1));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(2));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(3));
	pf->latch_event_flags = 0;
	spin_unlock_bh(&pf->ptp_rx_lock);

	/* Enable/disable the Tx timestamp interrupt based on user input. */
	regval = rd32(hw, I40E_PRTTSYN_CTL0);
	if (pf->ptp_tx)
		regval |= I40E_PRTTSYN_CTL0_TXTIME_INT_ENA_MASK;
	else
		regval &= ~I40E_PRTTSYN_CTL0_TXTIME_INT_ENA_MASK;
	wr32(hw, I40E_PRTTSYN_CTL0, regval);

	regval = rd32(hw, I40E_PFINT_ICR0_ENA);
	if (pf->ptp_tx)
		regval |= I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;
	else
		regval &= ~I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, regval);

	/* Although there is no simple on/off switch for Rx, we "disable" Rx
	 * timestamps by setting to V1 only mode and clear the UDP
	 * recognition. This ought to disable all PTP Rx timestamps as V1
	 * packets are always over UDP. Note that software is configured to
	 * ignore Rx timestamps via the pf->ptp_rx flag.
	 */
	regval = rd32(hw, I40E_PRTTSYN_CTL1);
	/* clear everything but the enable bit */
	regval &= I40E_PRTTSYN_CTL1_TSYNENA_MASK;
	/* now enable bits for desired Rx timestamps */
	regval |= tsyntype;
	wr32(hw, I40E_PRTTSYN_CTL1, regval);

	return 0;
}
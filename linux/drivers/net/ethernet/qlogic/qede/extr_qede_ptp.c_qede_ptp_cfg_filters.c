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
struct qede_ptp {int tx_type; int rx_filter; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  hw_ts_ioctl_called; } ;
struct qede_dev {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; struct qede_ptp* ptp; } ;
typedef  enum qed_ptp_hwtstamp_tx_type { ____Placeholder_qed_ptp_hwtstamp_tx_type } qed_ptp_hwtstamp_tx_type ;
typedef  enum qed_ptp_filter_type { ____Placeholder_qed_ptp_filter_type } qed_ptp_filter_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* cfg_filters ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EIO ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 146 
#define  HWTSTAMP_FILTER_NONE 145 
#define  HWTSTAMP_FILTER_NTP_ALL 144 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 141 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 140 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 139 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 136 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 133 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 132 
#define  HWTSTAMP_FILTER_SOME 131 
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int /*<<< orphan*/  QEDE_FLAGS_TX_TIMESTAMPING_EN ; 
 int QED_PTP_FILTER_ALL ; 
 int QED_PTP_FILTER_NONE ; 
 int QED_PTP_FILTER_V1_L4_EVENT ; 
 int QED_PTP_FILTER_V1_L4_GEN ; 
 int QED_PTP_FILTER_V2_EVENT ; 
 int QED_PTP_FILTER_V2_GEN ; 
 int QED_PTP_FILTER_V2_L2_EVENT ; 
 int QED_PTP_FILTER_V2_L2_GEN ; 
 int QED_PTP_FILTER_V2_L4_EVENT ; 
 int QED_PTP_FILTER_V2_L4_GEN ; 
 int QED_PTP_HWTSTAMP_TX_OFF ; 
 int QED_PTP_HWTSTAMP_TX_ON ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qede_ptp_cfg_filters(struct qede_dev *edev)
{
	enum qed_ptp_hwtstamp_tx_type tx_type = QED_PTP_HWTSTAMP_TX_ON;
	enum qed_ptp_filter_type rx_filter = QED_PTP_FILTER_NONE;
	struct qede_ptp *ptp = edev->ptp;

	if (!ptp)
		return -EIO;

	if (!ptp->hw_ts_ioctl_called) {
		DP_INFO(edev, "TS IOCTL not called\n");
		return 0;
	}

	switch (ptp->tx_type) {
	case HWTSTAMP_TX_ON:
		set_bit(QEDE_FLAGS_TX_TIMESTAMPING_EN, &edev->flags);
		tx_type = QED_PTP_HWTSTAMP_TX_ON;
		break;

	case HWTSTAMP_TX_OFF:
		clear_bit(QEDE_FLAGS_TX_TIMESTAMPING_EN, &edev->flags);
		tx_type = QED_PTP_HWTSTAMP_TX_OFF;
		break;

	case HWTSTAMP_TX_ONESTEP_SYNC:
		DP_ERR(edev, "One-step timestamping is not supported\n");
		return -ERANGE;
	}

	spin_lock_bh(&ptp->lock);
	switch (ptp->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		rx_filter = QED_PTP_FILTER_NONE;
		break;
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_NTP_ALL:
		ptp->rx_filter = HWTSTAMP_FILTER_NONE;
		rx_filter = QED_PTP_FILTER_ALL;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		rx_filter = QED_PTP_FILTER_V1_L4_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		/* Initialize PTP detection for UDP/IPv4 events */
		rx_filter = QED_PTP_FILTER_V1_L4_GEN;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		rx_filter = QED_PTP_FILTER_V2_L4_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		/* Initialize PTP detection for UDP/IPv4 or UDP/IPv6 events */
		rx_filter = QED_PTP_FILTER_V2_L4_GEN;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		rx_filter = QED_PTP_FILTER_V2_L2_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		/* Initialize PTP detection L2 events */
		rx_filter = QED_PTP_FILTER_V2_L2_GEN;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		rx_filter = QED_PTP_FILTER_V2_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		/* Initialize PTP detection L2, UDP/IPv4 or UDP/IPv6 events */
		rx_filter = QED_PTP_FILTER_V2_GEN;
		break;
	}

	ptp->ops->cfg_filters(edev->cdev, rx_filter, tx_type);

	spin_unlock_bh(&ptp->lock);

	return 0;
}
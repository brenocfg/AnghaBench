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
struct bnx2x {int tx_type; int rx_filter; int /*<<< orphan*/  flags; int /*<<< orphan*/  hwtstamp_ioctl_called; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 145 
#define  HWTSTAMP_FILTER_NONE 144 
#define  HWTSTAMP_FILTER_NTP_ALL 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 141 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 140 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 136 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 133 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 132 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 131 
#define  HWTSTAMP_FILTER_SOME 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_TIMESTAMPING_EN ; 
 int bnx2x_enable_ptp_packets (struct bnx2x*) ; 

int bnx2x_configure_ptp_filters(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int rc;

	if (!bp->hwtstamp_ioctl_called)
		return 0;

	switch (bp->tx_type) {
	case HWTSTAMP_TX_ON:
		bp->flags |= TX_TIMESTAMPING_EN;
		REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
		       NIG_REG_P0_TLLH_PTP_PARAM_MASK, 0x6AA);
		REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
		       NIG_REG_P0_TLLH_PTP_RULE_MASK, 0x3EEE);
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		BNX2X_ERR("One-step timestamping is not supported\n");
		return -ERANGE;
	}

	switch (bp->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		break;
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_NTP_ALL:
		bp->rx_filter = HWTSTAMP_FILTER_NONE;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		/* Initialize PTP detection for UDP/IPv4 events */
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
		       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7EE);
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
		       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FFE);
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		/* Initialize PTP detection for UDP/IPv4 or UDP/IPv6 events */
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
		       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7EA);
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
		       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FEE);
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		/* Initialize PTP detection L2 events */
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
		       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x6BF);
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
		       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3EFF);

		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		/* Initialize PTP detection L2, UDP/IPv4 or UDP/IPv6 events */
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
		       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x6AA);
		REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
		       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3EEE);
		break;
	}

	/* Indicate to FW that this PF expects recorded PTP packets */
	rc = bnx2x_enable_ptp_packets(bp);
	if (rc)
		return rc;

	/* Enable sending PTP packets to host */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x1);

	return 0;
}
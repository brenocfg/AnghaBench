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
struct net_device {int dummy; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
struct macb {int hw_dma_cap; struct hwtstamp_config tstamp_config; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
typedef  enum macb_bd_control { ____Placeholder_macb_bd_control } macb_bd_control ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 144 
#define  HWTSTAMP_FILTER_NONE 143 
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
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int HW_DMA_CAP_PTP ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  SRTSM ; 
 int TSTAMP_ALL_FRAMES ; 
 int TSTAMP_ALL_PTP_FRAMES ; 
 int TSTAMP_DISABLED ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  gem_ptp_set_one_step_sync (struct macb*,int) ; 
 scalar_t__ gem_ptp_set_ts_mode (struct macb*,int,int) ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 struct macb* netdev_priv (struct net_device*) ; 

int gem_set_hwtst(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	enum macb_bd_control tx_bd_control = TSTAMP_DISABLED;
	enum macb_bd_control rx_bd_control = TSTAMP_DISABLED;
	struct hwtstamp_config *tstamp_config;
	struct macb *bp = netdev_priv(dev);
	u32 regval;

	tstamp_config = &bp->tstamp_config;
	if ((bp->hw_dma_cap & HW_DMA_CAP_PTP) == 0)
		return -EOPNOTSUPP;

	if (copy_from_user(tstamp_config, ifr->ifr_data,
			   sizeof(*tstamp_config)))
		return -EFAULT;

	/* reserved for future extensions */
	if (tstamp_config->flags)
		return -EINVAL;

	switch (tstamp_config->tx_type) {
	case HWTSTAMP_TX_OFF:
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		if (gem_ptp_set_one_step_sync(bp, 1) != 0)
			return -ERANGE;
		/* fall through */
	case HWTSTAMP_TX_ON:
		tx_bd_control = TSTAMP_ALL_FRAMES;
		break;
	default:
		return -ERANGE;
	}

	switch (tstamp_config->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
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
		rx_bd_control =  TSTAMP_ALL_PTP_FRAMES;
		tstamp_config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		regval = macb_readl(bp, NCR);
		macb_writel(bp, NCR, (regval | MACB_BIT(SRTSM)));
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_ALL:
		rx_bd_control = TSTAMP_ALL_FRAMES;
		tstamp_config->rx_filter = HWTSTAMP_FILTER_ALL;
		break;
	default:
		tstamp_config->rx_filter = HWTSTAMP_FILTER_NONE;
		return -ERANGE;
	}

	if (gem_ptp_set_ts_mode(bp, tx_bd_control, rx_bd_control) != 0)
		return -ERANGE;

	if (copy_to_user(ifr->ifr_data, tstamp_config, sizeof(*tstamp_config)))
		return -EFAULT;
	else
		return 0;
}
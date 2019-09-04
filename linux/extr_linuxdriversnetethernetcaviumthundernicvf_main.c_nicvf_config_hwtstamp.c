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
struct nicvf {int hw_rx_tstamp; int /*<<< orphan*/  ptp_clock; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
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
#define  HWTSTAMP_FILTER_SOME 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_config_hw_rx_tstamp (struct nicvf*,int) ; 

__attribute__((used)) static int nicvf_config_hwtstamp(struct net_device *netdev, struct ifreq *ifr)
{
	struct hwtstamp_config config;
	struct nicvf *nic = netdev_priv(netdev);

	if (!nic->ptp_clock)
		return -ENODEV;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	/* reserved for future extensions */
	if (config.flags)
		return -EINVAL;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
	case HWTSTAMP_TX_ON:
		break;
	default:
		return -ERANGE;
	}

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		nic->hw_rx_tstamp = false;
		break;
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		nic->hw_rx_tstamp = true;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		break;
	default:
		return -ERANGE;
	}

	if (netif_running(netdev))
		nicvf_config_hw_rx_tstamp(nic, nic->hw_rx_tstamp);

	if (copy_to_user(ifr->ifr_data, &config, sizeof(config)))
		return -EFAULT;

	return 0;
}
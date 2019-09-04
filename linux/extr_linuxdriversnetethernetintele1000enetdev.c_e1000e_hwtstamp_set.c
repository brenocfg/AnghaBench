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
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int rx_filter; } ;
struct e1000_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 133 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 132 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 131 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 130 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 129 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 128 
 int HWTSTAMP_FILTER_SOME ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int e1000e_config_hwtstamp (struct e1000_adapter*,struct hwtstamp_config*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000e_hwtstamp_set(struct net_device *netdev, struct ifreq *ifr)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct hwtstamp_config config;
	int ret_val;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	ret_val = e1000e_config_hwtstamp(adapter, &config);
	if (ret_val)
		return ret_val;

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		/* With V2 type filters which specify a Sync or Delay Request,
		 * Path Delay Request/Response messages are also time stamped
		 * by hardware so notify the caller the requested packets plus
		 * some others are time stamped.
		 */
		config.rx_filter = HWTSTAMP_FILTER_SOME;
		break;
	default:
		break;
	}

	return copy_to_user(ifr->ifr_data, &config,
			    sizeof(config)) ? -EFAULT : 0;
}
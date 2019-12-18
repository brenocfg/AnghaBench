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
struct ptp_qoriq {int phc_index; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_ts_info {int phc_index; int so_timestamping; int tx_types; int rx_filters; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_ALL ; 
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct ptp_qoriq* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dpaa_get_ts_info(struct net_device *net_dev,
			    struct ethtool_ts_info *info)
{
	struct device *dev = net_dev->dev.parent;
	struct device_node *mac_node = dev->of_node;
	struct device_node *fman_node = NULL, *ptp_node = NULL;
	struct platform_device *ptp_dev = NULL;
	struct ptp_qoriq *ptp = NULL;

	info->phc_index = -1;

	fman_node = of_get_parent(mac_node);
	if (fman_node)
		ptp_node = of_parse_phandle(fman_node, "ptimer-handle", 0);

	if (ptp_node)
		ptp_dev = of_find_device_by_node(ptp_node);

	if (ptp_dev)
		ptp = platform_get_drvdata(ptp_dev);

	if (ptp)
		info->phc_index = ptp->phc_index;

	info->so_timestamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);

	return 0;
}
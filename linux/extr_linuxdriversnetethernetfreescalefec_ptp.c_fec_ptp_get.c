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
struct hwtstamp_config {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; scalar_t__ flags; } ;
struct fec_enet_private {scalar_t__ hwts_rx_en; scalar_t__ hwts_tx_en; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_ALL ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  HWTSTAMP_TX_ON ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

int fec_ptp_get(struct net_device *ndev, struct ifreq *ifr)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct hwtstamp_config config;

	config.flags = 0;
	config.tx_type = fep->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	config.rx_filter = (fep->hwts_rx_en ?
			    HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE);

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}
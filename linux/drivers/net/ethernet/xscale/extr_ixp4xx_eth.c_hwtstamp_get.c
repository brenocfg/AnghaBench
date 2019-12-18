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
struct port {int hwts_rx_en; scalar_t__ hwts_tx_en; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_PTP_V1_L4_SYNC ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  HWTSTAMP_TX_ON ; 
#define  PTP_MASTER_MODE 129 
#define  PTP_SLAVE_MODE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hwtstamp_get(struct net_device *netdev, struct ifreq *ifr)
{
	struct hwtstamp_config cfg;
	struct port *port = netdev_priv(netdev);

	cfg.flags = 0;
	cfg.tx_type = port->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;

	switch (port->hwts_rx_en) {
	case 0:
		cfg.rx_filter = HWTSTAMP_FILTER_NONE;
		break;
	case PTP_SLAVE_MODE:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_SYNC;
		break;
	case PTP_MASTER_MODE:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ;
		break;
	default:
		WARN_ON_ONCE(1);
		return -ERANGE;
	}

	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}
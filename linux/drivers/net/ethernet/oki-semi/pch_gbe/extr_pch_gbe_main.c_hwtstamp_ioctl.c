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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct pch_gbe_adapter {int hwts_rx_en; int hwts_tx_en; struct pci_dev* ptp_pdev; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {scalar_t__ tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int CAP_MODE0 ; 
 int CAP_MODE2 ; 
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_NONE 132 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 131 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 130 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 129 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 128 
 scalar_t__ HWTSTAMP_TX_OFF ; 
 scalar_t__ HWTSTAMP_TX_ON ; 
 int MASTER_MODE ; 
 int /*<<< orphan*/  PTP_L2_MULTICAST_SA ; 
 int /*<<< orphan*/  PTP_L4_MULTICAST_SA ; 
 int RX_SNAPSHOT_LOCKED ; 
 int SLAVE_MODE ; 
 int TX_SNAPSHOT_LOCKED ; 
 int V2_MODE ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_ch_control_write (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pch_ch_event_write (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pch_set_station_address (int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwtstamp_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct hwtstamp_config cfg;
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev;
	u8 station[20];

	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;

	if (cfg.flags) /* reserved for future extensions */
		return -EINVAL;

	/* Get ieee1588's dev information */
	pdev = adapter->ptp_pdev;

	if (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		return -ERANGE;

	switch (cfg.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		adapter->hwts_rx_en = 0;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		adapter->hwts_rx_en = 0;
		pch_ch_control_write(pdev, SLAVE_MODE | CAP_MODE0);
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		adapter->hwts_rx_en = 1;
		pch_ch_control_write(pdev, MASTER_MODE | CAP_MODE0);
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		adapter->hwts_rx_en = 1;
		pch_ch_control_write(pdev, V2_MODE | CAP_MODE2);
		strcpy(station, PTP_L4_MULTICAST_SA);
		pch_set_station_address(station, pdev);
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		adapter->hwts_rx_en = 1;
		pch_ch_control_write(pdev, V2_MODE | CAP_MODE2);
		strcpy(station, PTP_L2_MULTICAST_SA);
		pch_set_station_address(station, pdev);
		break;
	default:
		return -ERANGE;
	}

	adapter->hwts_tx_en = cfg.tx_type == HWTSTAMP_TX_ON;

	/* Clear out any old time stamps. */
	pch_ch_event_write(pdev, TX_SNAPSHOT_LOCKED | RX_SNAPSHOT_LOCKED);

	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}
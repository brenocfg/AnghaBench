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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_dev {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_LRO_MAX_WQE_NUM_DEFAULT ; 
 int /*<<< orphan*/  HINIC_LRO_RX_TIMER_DEFAULT ; 
 int /*<<< orphan*/  HINIC_RX_CSUM_OFFLOAD_EN ; 
 int /*<<< orphan*/  HINIC_TSO_DISABLE ; 
 int /*<<< orphan*/  HINIC_TSO_ENABLE ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int hinic_port_set_tso (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 int hinic_set_rx_csum_offload (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 int hinic_set_rx_lro_state (struct hinic_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hinic_set_rx_vlan_offload (struct hinic_dev*,int) ; 

__attribute__((used)) static int set_features(struct hinic_dev *nic_dev,
			netdev_features_t pre_features,
			netdev_features_t features, bool force_change)
{
	netdev_features_t changed = force_change ? ~0 : pre_features ^ features;
	u32 csum_en = HINIC_RX_CSUM_OFFLOAD_EN;
	int err = 0;

	if (changed & NETIF_F_TSO)
		err = hinic_port_set_tso(nic_dev, (features & NETIF_F_TSO) ?
					 HINIC_TSO_ENABLE : HINIC_TSO_DISABLE);

	if (changed & NETIF_F_RXCSUM)
		err = hinic_set_rx_csum_offload(nic_dev, csum_en);

	if (changed & NETIF_F_LRO) {
		err = hinic_set_rx_lro_state(nic_dev,
					     !!(features & NETIF_F_LRO),
					     HINIC_LRO_RX_TIMER_DEFAULT,
					     HINIC_LRO_MAX_WQE_NUM_DEFAULT);
	}

	if (changed & NETIF_F_HW_VLAN_CTAG_RX)
		err = hinic_set_rx_vlan_offload(nic_dev,
						!!(features &
						   NETIF_F_HW_VLAN_CTAG_RX));

	return err;
}
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
struct qlcnic_adapter {int offload_flags; int rx_csum; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 scalar_t__ QLCNIC_IS_TSO_CAPABLE (struct qlcnic_adapter*) ; 

__attribute__((used)) static netdev_features_t qlcnic_process_flags(struct qlcnic_adapter *adapter,
					      netdev_features_t features)
{
	u32 offload_flags = adapter->offload_flags;

	if (offload_flags & BIT_0) {
		features |= NETIF_F_RXCSUM | NETIF_F_IP_CSUM |
			    NETIF_F_IPV6_CSUM;
		adapter->rx_csum = 1;
		if (QLCNIC_IS_TSO_CAPABLE(adapter)) {
			if (!(offload_flags & BIT_1))
				features &= ~NETIF_F_TSO;
			else
				features |= NETIF_F_TSO;

			if (!(offload_flags & BIT_2))
				features &= ~NETIF_F_TSO6;
			else
				features |= NETIF_F_TSO6;
		}
	} else {
		features &= ~(NETIF_F_RXCSUM |
			      NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM);

		if (QLCNIC_IS_TSO_CAPABLE(adapter))
			features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
		adapter->rx_csum = 0;
	}

	return features;
}
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
struct ethtool_ringparam {void* tx_pending; void* rx_pending; void* tx_max_pending; void* rx_max_pending; } ;

/* Variables and functions */
 void* HINIC_RQ_DEPTH ; 
 void* HINIC_SQ_DEPTH ; 

__attribute__((used)) static void hinic_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	ring->rx_max_pending = HINIC_RQ_DEPTH;
	ring->tx_max_pending = HINIC_SQ_DEPTH;
	ring->rx_pending = HINIC_RQ_DEPTH;
	ring->tx_pending = HINIC_SQ_DEPTH;
}
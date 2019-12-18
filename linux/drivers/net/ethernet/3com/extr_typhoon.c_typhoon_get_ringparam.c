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
 void* RXENT_ENTRIES ; 
 void* TXLO_ENTRIES ; 

__attribute__((used)) static void
typhoon_get_ringparam(struct net_device *dev, struct ethtool_ringparam *ering)
{
	ering->rx_max_pending = RXENT_ENTRIES;
	ering->tx_max_pending = TXLO_ENTRIES - 1;

	ering->rx_pending = RXENT_ENTRIES;
	ering->tx_pending = TXLO_ENTRIES - 1;
}
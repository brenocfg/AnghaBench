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
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CTRL_DBG ; 
 int NETIF_F_RXALL ; 

__attribute__((used)) static void __atl1e_rx_mode(netdev_features_t features, u32 *mac_ctrl_data)
{

	if (features & NETIF_F_RXALL) {
		/* enable RX of ALL frames */
		*mac_ctrl_data |= MAC_CTRL_DBG;
	} else {
		/* disable RX of ALL frames */
		*mac_ctrl_data &= ~MAC_CTRL_DBG;
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  dm_CheckRxAggregation (struct net_device*) ; 
 int /*<<< orphan*/  dm_bandwidth_autoswitch (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_edca_turbo (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_fsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_pbc_gpio (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_rate_adaptive (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_rx_path_selection (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_txpower_tracking (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_txrateandretrycount (struct net_device*) ; 
 int /*<<< orphan*/  dm_ctrl_initgain_byrssi (struct net_device*) ; 
 int /*<<< orphan*/  dm_ctstoself (struct net_device*) ; 
 int /*<<< orphan*/  dm_dynamic_txpower (struct net_device*) ; 
 int /*<<< orphan*/  dm_send_rssi_tofw (struct net_device*) ; 

void hal_dm_watchdog(struct net_device *dev)
{
	/*struct r8192_priv *priv = ieee80211_priv(dev);*/

	/*static u8	previous_bssid[6] ={0};*/

	/*Add by amy 2008/05/15 ,porting from windows code.*/
	dm_check_rate_adaptive(dev);
	dm_dynamic_txpower(dev);
	dm_check_txrateandretrycount(dev);
	dm_check_txpower_tracking(dev);
	dm_ctrl_initgain_byrssi(dev);
	dm_check_edca_turbo(dev);
	dm_bandwidth_autoswitch(dev);
	dm_check_rx_path_selection(dev);
	dm_check_fsync(dev);

	/* Add by amy 2008-05-15 porting from windows code. */
	dm_check_pbc_gpio(dev);
	dm_send_rssi_tofw(dev);
	dm_ctstoself(dev);
#ifdef USB_RX_AGGREGATION_SUPPORT
	dm_CheckRxAggregation(dev);
#endif
}
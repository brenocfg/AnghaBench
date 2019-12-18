#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct r8192_priv {int /*<<< orphan*/  undecorated_smoothed_pwdb; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_connect_state; int /*<<< orphan*/  pre_connect_state; scalar_t__ dig_algorithm_switch; int /*<<< orphan*/  rssi_val; int /*<<< orphan*/  dig_state; int /*<<< orphan*/  dig_enable_flag; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_CONNECT ; 
 int /*<<< orphan*/  DIG_DISCONNECT ; 
 int /*<<< orphan*/  DM_STA_DIG_OFF ; 
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  UFWP ; 
 int /*<<< orphan*/  bMaskByte1 ; 
 int /*<<< orphan*/  dm_cs_ratio (struct net_device*) ; 
 TYPE_2__ dm_digtable ; 
 int /*<<< orphan*/  dm_initial_gain (struct net_device*) ; 
 int /*<<< orphan*/  dm_pd_th (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_ctrl_initgain_byrssi_by_driverrssi(
	struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8 i;
	static u8	fw_dig;

	if (!dm_digtable.dig_enable_flag)
		return;

	/*DbgPrint("Dig by Sw Rssi\n");*/
	if (dm_digtable.dig_algorithm_switch)	/* if switched algorithm, we have to disable FW Dig. */
		fw_dig = 0;

	if (fw_dig <= 3) { /* execute several times to make sure the FW Dig is disabled */
		/* FW DIG Off */
		for (i = 0; i < 3; i++)
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	/* Only clear byte 1 and rewrite. */
		fw_dig++;
		dm_digtable.dig_state = DM_STA_DIG_OFF;	/* fw dig off. */
	}

	if (priv->ieee80211->state == IEEE80211_LINKED)
		dm_digtable.cur_connect_state = DIG_CONNECT;
	else
		dm_digtable.cur_connect_state = DIG_DISCONNECT;

	/*DbgPrint("DM_DigTable.PreConnectState = %d, DM_DigTable.CurConnectState = %d\n",
		DM_DigTable.PreConnectState, DM_DigTable.CurConnectState);*/

	dm_digtable.rssi_val = priv->undecorated_smoothed_pwdb;
	/*DbgPrint("DM_DigTable.Rssi_val = %d\n", DM_DigTable.Rssi_val);*/
	dm_initial_gain(dev);
	dm_pd_th(dev);
	dm_cs_ratio(dev);
	if (dm_digtable.dig_algorithm_switch)
		dm_digtable.dig_algorithm_switch = 0;
	dm_digtable.pre_connect_state = dm_digtable.cur_connect_state;

}
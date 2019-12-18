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
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_RSSI ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_send_rssi_tofw(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	/* If we test chariot, we should stop the TX command ?
	 * Because 92E will always silent reset when we send tx command. We use register
	 * 0x1e0(byte) to notify driver.
	 */
	write_nic_byte(dev, DRIVER_RSSI, (u8)priv->undecorated_smoothed_pwdb);
}
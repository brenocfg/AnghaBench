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
typedef  int u8 ;
struct r8192_priv {int /*<<< orphan*/  watch_dog_timer; int /*<<< orphan*/ * txqueue_to_outpipemap; int /*<<< orphan*/  stats; } ;
struct net_device {int dummy; } ;
struct Stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*) ; 
 short ENOMEM ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  init_hal_dm (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8192_get_channel_map (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_get_eeprom_size (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_init_priv_lock (struct r8192_priv*) ; 
 int /*<<< orphan*/  rtl8192_init_priv_task (struct net_device*) ; 
 int rtl8192_init_priv_variable (struct net_device*) ; 
 int rtl8192_read_eeprom_info (struct net_device*) ; 
 scalar_t__ rtl8192_usb_initendpoints (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watch_dog_timer_callback ; 

__attribute__((used)) static short rtl8192_init(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	int err;

	memset(&(priv->stats), 0, sizeof(struct Stats));
	memset(priv->txqueue_to_outpipemap, 0, 9);
#ifdef PIPE12
	{
		int i = 0;
		u8 queuetopipe[] = {3, 2, 1, 0, 4, 8, 7, 6, 5};

		memcpy(priv->txqueue_to_outpipemap, queuetopipe, 9);
	}
#else
	{
		u8 queuetopipe[] = {3, 2, 1, 0, 4, 4, 0, 4, 4};

		memcpy(priv->txqueue_to_outpipemap, queuetopipe, 9);
	}
#endif
	err = rtl8192_init_priv_variable(dev);
	if (err)
		return err;

	rtl8192_init_priv_lock(priv);
	rtl8192_init_priv_task(dev);
	rtl8192_get_eeprom_size(dev);
	err = rtl8192_read_eeprom_info(dev);
	if (err) {
		DMESG("Reading EEPROM info failed");
		return err;
	}
	rtl8192_get_channel_map(dev);
	init_hal_dm(dev);
	timer_setup(&priv->watch_dog_timer, watch_dog_timer_callback, 0);
	if (rtl8192_usb_initendpoints(dev) != 0) {
		DMESG("Endopoints initialization failed");
		return -ENOMEM;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct b43_phy {TYPE_1__* ops; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct TYPE_2__ {int (* switch_channel ) (struct b43_wldev*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_CHAN ; 
 unsigned int B43_SHM_SH_CHAN_40MHZ ; 
 unsigned int B43_SHM_SH_CHAN_5GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 unsigned int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct b43_wldev*,unsigned int) ; 

int b43_switch_channel(struct b43_wldev *dev, unsigned int new_channel)
{
	struct b43_phy *phy = &(dev->phy);
	u16 channelcookie, savedcookie;
	int err;

	/* First we set the channel radio code to prevent the
	 * firmware from sending ghost packets.
	 */
	channelcookie = new_channel;
	if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		channelcookie |= B43_SHM_SH_CHAN_5GHZ;
	/* FIXME: set 40Mhz flag if required */
	if (0)
		channelcookie |= B43_SHM_SH_CHAN_40MHZ;
	savedcookie = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_CHAN);
	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_CHAN, channelcookie);

	/* Now try to switch the PHY hardware channel. */
	err = phy->ops->switch_channel(dev, new_channel);
	if (err)
		goto err_restore_cookie;

	/* Wait for the radio to tune to the channel and stabilize. */
	msleep(8);

	return 0;

err_restore_cookie:
	b43_shm_write16(dev, B43_SHM_SHARED,
			B43_SHM_SH_CHAN, savedcookie);

	return err;
}
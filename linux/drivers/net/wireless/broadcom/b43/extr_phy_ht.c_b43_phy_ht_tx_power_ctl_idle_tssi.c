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
typedef  int u16 ;
struct TYPE_2__ {struct b43_phy_ht* ht; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_ht {int* idle_tssi; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HT_RSSI_TSSI_2G ; 
 int /*<<< orphan*/  b43_phy_ht_poll_rssi (struct b43_wldev*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  b43_phy_ht_reset_cca (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_stop_playback (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_tone (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int const,int) ; 
 int b43_phy_read (struct b43_wldev*,int const) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_phy_ht_tx_power_ctl_idle_tssi(struct b43_wldev *dev)
{
	struct b43_phy_ht *phy_ht = dev->phy.ht;
	static const u16 base[] = { 0x840, 0x860, 0x880 };
	u16 save_regs[3][3];
	s32 rssi_buf[6];
	int core;

	for (core = 0; core < 3; core++) {
		save_regs[core][1] = b43_phy_read(dev, base[core] + 6);
		save_regs[core][2] = b43_phy_read(dev, base[core] + 7);
		save_regs[core][0] = b43_phy_read(dev, base[core] + 0);

		b43_phy_write(dev, base[core] + 6, 0);
		b43_phy_mask(dev, base[core] + 7, ~0xF); /* 0xF? Or just 0x6? */
		b43_phy_set(dev, base[core] + 0, 0x0400);
		b43_phy_set(dev, base[core] + 0, 0x1000);
	}

	b43_phy_ht_tx_tone(dev);
	udelay(20);
	b43_phy_ht_poll_rssi(dev, HT_RSSI_TSSI_2G, rssi_buf, 1);
	b43_phy_ht_stop_playback(dev);
	b43_phy_ht_reset_cca(dev);

	phy_ht->idle_tssi[0] = rssi_buf[0] & 0xff;
	phy_ht->idle_tssi[1] = rssi_buf[2] & 0xff;
	phy_ht->idle_tssi[2] = rssi_buf[4] & 0xff;

	for (core = 0; core < 3; core++) {
		b43_phy_write(dev, base[core] + 0, save_regs[core][0]);
		b43_phy_write(dev, base[core] + 6, save_regs[core][1]);
		b43_phy_write(dev, base[core] + 7, save_regs[core][2]);
	}
}
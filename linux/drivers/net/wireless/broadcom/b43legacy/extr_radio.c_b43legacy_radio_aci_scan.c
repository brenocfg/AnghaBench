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
struct b43legacy_phy {unsigned int channel; scalar_t__ type; scalar_t__ rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int B43legacy_PHY_G_CRS ; 
 int abs (unsigned int) ; 
 int /*<<< orphan*/  b43legacy_phy_lock (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_unlock (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_aci_detect (struct b43legacy_wldev*,unsigned int) ; 
 int /*<<< orphan*/  b43legacy_radio_lock (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_unlock (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_set_all_gains (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_set_original_gains (struct b43legacy_wldev*) ; 

u8 b43legacy_radio_aci_scan(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u8 ret[13] = { 0 };
	unsigned int channel = phy->channel;
	unsigned int i;
	unsigned int j;
	unsigned int start;
	unsigned int end;

	if (!((phy->type == B43legacy_PHYTYPE_G) && (phy->rev > 0)))
		return 0;

	b43legacy_phy_lock(dev);
	b43legacy_radio_lock(dev);
	b43legacy_phy_write(dev, 0x0802,
			    b43legacy_phy_read(dev, 0x0802) & 0xFFFC);
	b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
			    b43legacy_phy_read(dev, B43legacy_PHY_G_CRS)
			    & 0x7FFF);
	b43legacy_set_all_gains(dev, 3, 8, 1);

	start = (channel - 5 > 0) ? channel - 5 : 1;
	end = (channel + 5 < 14) ? channel + 5 : 13;

	for (i = start; i <= end; i++) {
		if (abs(channel - i) > 2)
			ret[i-1] = b43legacy_radio_aci_detect(dev, i);
	}
	b43legacy_radio_selectchannel(dev, channel, 0);
	b43legacy_phy_write(dev, 0x0802,
			    (b43legacy_phy_read(dev, 0x0802) & 0xFFFC)
			    | 0x0003);
	b43legacy_phy_write(dev, 0x0403,
			    b43legacy_phy_read(dev, 0x0403) & 0xFFF8);
	b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
			    b43legacy_phy_read(dev, B43legacy_PHY_G_CRS)
			    | 0x8000);
	b43legacy_set_original_gains(dev);
	for (i = 0; i < 13; i++) {
		if (!ret[i])
			continue;
		end = (i + 5 < 13) ? i + 5 : 13;
		for (j = i; j < end; j++)
			ret[j] = 1;
	}
	b43legacy_radio_unlock(dev);
	b43legacy_phy_unlock(dev);

	return ret[channel - 1];
}
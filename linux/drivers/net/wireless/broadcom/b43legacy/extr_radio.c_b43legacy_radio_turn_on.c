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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int valid; int rfover; int rfoverval; } ;
struct b43legacy_phy {int radio_on; int type; int /*<<< orphan*/  channel; TYPE_1__ radio_off_context; int /*<<< orphan*/  gmode; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int B43legacy_PHY_RFOVER ; 
 int B43legacy_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  B43legacy_RADIO_DEFAULT_CHANNEL_BG ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_selectchannel (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  might_sleep () ; 

void b43legacy_radio_turn_on(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	int err;
	u8 channel;

	might_sleep();

	if (phy->radio_on)
		return;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
	case B43legacy_PHYTYPE_G:
		b43legacy_phy_write(dev, 0x0015, 0x8000);
		b43legacy_phy_write(dev, 0x0015, 0xCC00);
		b43legacy_phy_write(dev, 0x0015,
				    (phy->gmode ? 0x00C0 : 0x0000));
		if (phy->radio_off_context.valid) {
			/* Restore the RFover values. */
			b43legacy_phy_write(dev, B43legacy_PHY_RFOVER,
					    phy->radio_off_context.rfover);
			b43legacy_phy_write(dev, B43legacy_PHY_RFOVERVAL,
					    phy->radio_off_context.rfoverval);
			phy->radio_off_context.valid = false;
		}
		channel = phy->channel;
		err = b43legacy_radio_selectchannel(dev,
					B43legacy_RADIO_DEFAULT_CHANNEL_BG, 1);
		err |= b43legacy_radio_selectchannel(dev, channel, 0);
		B43legacy_WARN_ON(err);
		break;
	default:
		B43legacy_BUG_ON(1);
	}
	phy->radio_on = true;
}
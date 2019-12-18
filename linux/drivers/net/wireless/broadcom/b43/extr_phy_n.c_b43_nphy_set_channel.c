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
typedef  int u16 ;
struct ieee80211_channel {scalar_t__ band; int /*<<< orphan*/  hw_value; int /*<<< orphan*/  center_freq; } ;
struct b43_phy {int rev; int channel_type; int radio_rev; int /*<<< orphan*/  channel; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_n_sfo_cfg {int dummy; } ;
struct b43_nphy_chantabent_rev7_2g {struct b43_phy_n_sfo_cfg phy_regs; } ;
struct b43_nphy_chantabent_rev7 {struct b43_phy_n_sfo_cfg phy_regs; } ;
struct b43_nphy_channeltab_entry_rev3 {struct b43_phy_n_sfo_cfg const phy_regs; } ;
struct b43_nphy_channeltab_entry_rev2 {struct b43_phy_n_sfo_cfg const phy_regs; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;

/* Variables and functions */
 int B2055_MASTER1 ; 
 int B43_NPHY_RXCTL ; 
 int B43_NPHY_RXCTL_BSELU20 ; 
 int ESRCH ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int NL80211_CHAN_HT40MINUS ; 
 int NL80211_CHAN_HT40PLUS ; 
 int R2057_TIA_CONFIG_CORE0 ; 
 int R2057_TIA_CONFIG_CORE1 ; 
 scalar_t__ b43_channel_type_is_40mhz (int) ; 
 int /*<<< orphan*/  b43_nphy_channel_setup (struct b43_wldev*,struct b43_phy_n_sfo_cfg const*,struct ieee80211_channel*) ; 
 struct b43_nphy_channeltab_entry_rev2* b43_nphy_get_chantabent_rev2 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_get_chantabent_rev3 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_2055_setup (struct b43_wldev*,struct b43_nphy_channeltab_entry_rev2 const*) ; 
 int /*<<< orphan*/  b43_radio_2056_setup (struct b43_wldev*,struct b43_nphy_channeltab_entry_rev3 const*) ; 
 int /*<<< orphan*/  b43_radio_2057_setup (struct b43_wldev*,struct b43_nphy_chantabent_rev7 const*,struct b43_nphy_chantabent_rev7_2g const*) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  r2057_get_chantabent_rev7 (struct b43_wldev*,int /*<<< orphan*/ ,struct b43_nphy_chantabent_rev7 const**,struct b43_nphy_chantabent_rev7_2g const**) ; 

__attribute__((used)) static int b43_nphy_set_channel(struct b43_wldev *dev,
				struct ieee80211_channel *channel,
				enum nl80211_channel_type channel_type)
{
	struct b43_phy *phy = &dev->phy;

	const struct b43_nphy_channeltab_entry_rev2 *tabent_r2 = NULL;
	const struct b43_nphy_channeltab_entry_rev3 *tabent_r3 = NULL;
	const struct b43_nphy_chantabent_rev7 *tabent_r7 = NULL;
	const struct b43_nphy_chantabent_rev7_2g *tabent_r7_2g = NULL;

	u8 tmp;

	if (phy->rev >= 19) {
		return -ESRCH;
		/* TODO */
	} else if (phy->rev >= 7) {
		r2057_get_chantabent_rev7(dev, channel->center_freq,
					  &tabent_r7, &tabent_r7_2g);
		if (!tabent_r7 && !tabent_r7_2g)
			return -ESRCH;
	} else if (phy->rev >= 3) {
		tabent_r3 = b43_nphy_get_chantabent_rev3(dev,
							channel->center_freq);
		if (!tabent_r3)
			return -ESRCH;
	} else {
		tabent_r2 = b43_nphy_get_chantabent_rev2(dev,
							channel->hw_value);
		if (!tabent_r2)
			return -ESRCH;
	}

	/* Channel is set later in common code, but we need to set it on our
	   own to let this function's subcalls work properly. */
	phy->channel = channel->hw_value;

#if 0
	if (b43_channel_type_is_40mhz(phy->channel_type) !=
		b43_channel_type_is_40mhz(channel_type))
		; /* TODO: BMAC BW Set (channel_type) */
#endif

	if (channel_type == NL80211_CHAN_HT40PLUS) {
		b43_phy_set(dev, B43_NPHY_RXCTL, B43_NPHY_RXCTL_BSELU20);
		if (phy->rev >= 7)
			b43_phy_set(dev, 0x310, 0x8000);
	} else if (channel_type == NL80211_CHAN_HT40MINUS) {
		b43_phy_mask(dev, B43_NPHY_RXCTL, ~B43_NPHY_RXCTL_BSELU20);
		if (phy->rev >= 7)
			b43_phy_mask(dev, 0x310, (u16)~0x8000);
	}

	if (phy->rev >= 19) {
		/* TODO */
	} else if (phy->rev >= 7) {
		const struct b43_phy_n_sfo_cfg *phy_regs = tabent_r7 ?
			&(tabent_r7->phy_regs) : &(tabent_r7_2g->phy_regs);

		if (phy->radio_rev <= 4 || phy->radio_rev == 6) {
			tmp = (channel->band == NL80211_BAND_5GHZ) ? 2 : 0;
			b43_radio_maskset(dev, R2057_TIA_CONFIG_CORE0, ~2, tmp);
			b43_radio_maskset(dev, R2057_TIA_CONFIG_CORE1, ~2, tmp);
		}

		b43_radio_2057_setup(dev, tabent_r7, tabent_r7_2g);
		b43_nphy_channel_setup(dev, phy_regs, channel);
	} else if (phy->rev >= 3) {
		tmp = (channel->band == NL80211_BAND_5GHZ) ? 4 : 0;
		b43_radio_maskset(dev, 0x08, 0xFFFB, tmp);
		b43_radio_2056_setup(dev, tabent_r3);
		b43_nphy_channel_setup(dev, &(tabent_r3->phy_regs), channel);
	} else {
		tmp = (channel->band == NL80211_BAND_5GHZ) ? 0x0020 : 0x0050;
		b43_radio_maskset(dev, B2055_MASTER1, 0xFF8F, tmp);
		b43_radio_2055_setup(dev, tabent_r2);
		b43_nphy_channel_setup(dev, &(tabent_r2->phy_regs), channel);
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int /*<<< orphan*/  hw_value; int /*<<< orphan*/  bitrate; } ;
struct b43legacy_wldev {TYPE_3__* wl; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int B43legacy_SHM_SH_CCKBASIC ; 
 int B43legacy_SHM_SH_CCKDIRECT ; 
 int B43legacy_SHM_SH_OFDMBASIC ; 
 int B43legacy_SHM_SH_OFDMDIRECT ; 
 size_t NL80211_BAND_2GHZ ; 
 scalar_t__ b43legacy_is_cck_rate (int /*<<< orphan*/ ) ; 
 int b43legacy_plcp_get_ratecode_cck (int /*<<< orphan*/ ) ; 
 int b43legacy_plcp_get_ratecode_ofdm (int /*<<< orphan*/ ) ; 
 int b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,int) ; 
 struct ieee80211_rate* ieee80211_get_response_rate (struct ieee80211_supported_band*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_update_basic_rates(struct b43legacy_wldev *dev, u32 brates)
{
	struct ieee80211_supported_band *sband =
		dev->wl->hw->wiphy->bands[NL80211_BAND_2GHZ];
	struct ieee80211_rate *rate;
	int i;
	u16 basic, direct, offset, basic_offset, rateptr;

	for (i = 0; i < sband->n_bitrates; i++) {
		rate = &sband->bitrates[i];

		if (b43legacy_is_cck_rate(rate->hw_value)) {
			direct = B43legacy_SHM_SH_CCKDIRECT;
			basic = B43legacy_SHM_SH_CCKBASIC;
			offset = b43legacy_plcp_get_ratecode_cck(rate->hw_value);
			offset &= 0xF;
		} else {
			direct = B43legacy_SHM_SH_OFDMDIRECT;
			basic = B43legacy_SHM_SH_OFDMBASIC;
			offset = b43legacy_plcp_get_ratecode_ofdm(rate->hw_value);
			offset &= 0xF;
		}

		rate = ieee80211_get_response_rate(sband, brates, rate->bitrate);

		if (b43legacy_is_cck_rate(rate->hw_value)) {
			basic_offset = b43legacy_plcp_get_ratecode_cck(rate->hw_value);
			basic_offset &= 0xF;
		} else {
			basic_offset = b43legacy_plcp_get_ratecode_ofdm(rate->hw_value);
			basic_offset &= 0xF;
		}

		/*
		 * Get the pointer that we need to point to
		 * from the direct map
		 */
		rateptr = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
					       direct + 2 * basic_offset);
		/* and write it to the basic map */
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
				      basic + 2 * offset, rateptr);
	}
}
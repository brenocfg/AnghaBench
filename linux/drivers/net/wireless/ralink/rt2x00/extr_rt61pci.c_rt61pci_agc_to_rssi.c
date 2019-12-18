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
struct rt2x00_dev {int lna_gain; scalar_t__ curr_band; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RXD_W1_RSSI_AGC ; 
 int /*<<< orphan*/  RXD_W1_RSSI_LNA ; 
 int rt2x00_get_field32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt61pci_agc_to_rssi(struct rt2x00_dev *rt2x00dev, int rxd_w1)
{
	u8 offset = rt2x00dev->lna_gain;
	u8 lna;

	lna = rt2x00_get_field32(rxd_w1, RXD_W1_RSSI_LNA);
	switch (lna) {
	case 3:
		offset += 90;
		break;
	case 2:
		offset += 74;
		break;
	case 1:
		offset += 64;
		break;
	default:
		return 0;
	}

	if (rt2x00dev->curr_band == NL80211_BAND_5GHZ) {
		if (lna == 3 || lna == 2)
			offset += 10;
	}

	return rt2x00_get_field32(rxd_w1, RXD_W1_RSSI_AGC) * 2 - offset;
}
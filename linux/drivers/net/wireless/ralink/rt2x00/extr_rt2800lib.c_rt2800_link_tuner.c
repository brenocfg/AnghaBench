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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int rt; } ;
struct rt2x00_dev {int /*<<< orphan*/  curr_band; TYPE_1__ chip; } ;
struct link_qual {int rssi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  REV_RT2860C ; 
 int /*<<< orphan*/  RT2860 ; 
#define  RT3572 131 
#define  RT3593 130 
#define  RT3883 129 
#define  RT5592 128 
 int rt2800_get_default_vgc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_set_vgc (struct rt2x00_dev*,struct link_qual*,int) ; 
 scalar_t__ rt2x00_rt_rev (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_link_tuner(struct rt2x00_dev *rt2x00dev, struct link_qual *qual,
		       const u32 count)
{
	u8 vgc;

	if (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C))
		return;

	/* When RSSI is better than a certain threshold, increase VGC
	 * with a chip specific value in order to improve the balance
	 * between sensibility and noise isolation.
	 */

	vgc = rt2800_get_default_vgc(rt2x00dev);

	switch (rt2x00dev->chip.rt) {
	case RT3572:
	case RT3593:
		if (qual->rssi > -65) {
			if (rt2x00dev->curr_band == NL80211_BAND_2GHZ)
				vgc += 0x20;
			else
				vgc += 0x10;
		}
		break;

	case RT3883:
		if (qual->rssi > -65)
			vgc += 0x10;
		break;

	case RT5592:
		if (qual->rssi > -65)
			vgc += 0x20;
		break;

	default:
		if (qual->rssi > -80)
			vgc += 0x10;
		break;
	}

	rt2800_set_vgc(rt2x00dev, qual, vgc);
}
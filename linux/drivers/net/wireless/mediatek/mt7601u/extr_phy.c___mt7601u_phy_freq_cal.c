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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int adjusting; int freq; } ;
struct mt7601u_dev {TYPE_1__ freq_cal; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 unsigned long MT_FREQ_CAL_ADJ_INTERVAL ; 
 unsigned long MT_FREQ_CAL_CHECK_INTERVAL ; 
 scalar_t__ MT_FREQ_OFFSET_INVALID ; 
#define  MT_PHY_TYPE_CCK 131 
#define  MT_PHY_TYPE_HT 130 
#define  MT_PHY_TYPE_HT_GF 129 
#define  MT_PHY_TYPE_OFDM 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  mt7601u_rf_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt7601u_vco_cal (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  trace_freq_cal_adjust (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  trace_freq_cal_offset (struct mt7601u_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static unsigned long
__mt7601u_phy_freq_cal(struct mt7601u_dev *dev, s8 last_offset, u8 phy_mode)
{
	u8 activate_threshold, deactivate_threshold;

	trace_freq_cal_offset(dev, phy_mode, last_offset);

	/* No beacons received - reschedule soon */
	if (last_offset == MT_FREQ_OFFSET_INVALID)
		return MT_FREQ_CAL_ADJ_INTERVAL;

	switch (phy_mode) {
	case MT_PHY_TYPE_CCK:
		activate_threshold = 19;
		deactivate_threshold = 5;
		break;
	case MT_PHY_TYPE_OFDM:
		activate_threshold = 102;
		deactivate_threshold = 32;
		break;
	case MT_PHY_TYPE_HT:
	case MT_PHY_TYPE_HT_GF:
		activate_threshold = 82;
		deactivate_threshold = 20;
		break;
	default:
		WARN_ON(1);
		return MT_FREQ_CAL_CHECK_INTERVAL;
	}

	if (abs(last_offset) >= activate_threshold)
		dev->freq_cal.adjusting = true;
	else if (abs(last_offset) <= deactivate_threshold)
		dev->freq_cal.adjusting = false;

	if (!dev->freq_cal.adjusting)
		return MT_FREQ_CAL_CHECK_INTERVAL;

	if (last_offset > deactivate_threshold) {
		if (dev->freq_cal.freq > 0)
			dev->freq_cal.freq--;
		else
			dev->freq_cal.adjusting = false;
	} else if (last_offset < -deactivate_threshold) {
		if (dev->freq_cal.freq < 0xbf)
			dev->freq_cal.freq++;
		else
			dev->freq_cal.adjusting = false;
	}

	trace_freq_cal_adjust(dev, dev->freq_cal.freq);
	mt7601u_rf_wr(dev, 0, 12, dev->freq_cal.freq);
	mt7601u_vco_cal(dev);

	return dev->freq_cal.adjusting ? MT_FREQ_CAL_ADJ_INTERVAL :
					 MT_FREQ_CAL_CHECK_INTERVAL;
}
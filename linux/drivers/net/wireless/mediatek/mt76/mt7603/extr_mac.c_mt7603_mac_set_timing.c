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
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt7603_dev {int coverage_class; int slottime; TYPE_3__ mt76; } ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int MT7603_CFEND_RATE_11B ; 
 int MT7603_CFEND_RATE_DEFAULT ; 
 int /*<<< orphan*/  MT_AGG_CONTROL ; 
 int /*<<< orphan*/  MT_AGG_CONTROL_CFEND_RATE ; 
 int /*<<< orphan*/  MT_ARB_SCR ; 
 int MT_ARB_SCR_RX_DISABLE ; 
 int MT_ARB_SCR_TX_DISABLE ; 
 int /*<<< orphan*/  MT_IFS ; 
 int /*<<< orphan*/  MT_IFS_EIFS ; 
 int /*<<< orphan*/  MT_IFS_RIFS ; 
 int /*<<< orphan*/  MT_IFS_SIFS ; 
 int /*<<< orphan*/  MT_IFS_SLOT ; 
 int /*<<< orphan*/  MT_TIMEOUT_CCK ; 
 int /*<<< orphan*/  MT_TIMEOUT_OFDM ; 
 int /*<<< orphan*/  MT_TIMEOUT_VAL_CCA ; 
 int /*<<< orphan*/  MT_TIMEOUT_VAL_PLCP ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void mt7603_mac_set_timing(struct mt7603_dev *dev)
{
	u32 cck = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 231) |
		  FIELD_PREP(MT_TIMEOUT_VAL_CCA, 48);
	u32 ofdm = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, 60) |
		   FIELD_PREP(MT_TIMEOUT_VAL_CCA, 24);
	int offset = 3 * dev->coverage_class;
	u32 reg_offset = FIELD_PREP(MT_TIMEOUT_VAL_PLCP, offset) |
			 FIELD_PREP(MT_TIMEOUT_VAL_CCA, offset);
	int sifs;
	u32 val;

	if (dev->mt76.chandef.chan->band == NL80211_BAND_5GHZ)
		sifs = 16;
	else
		sifs = 10;

	mt76_set(dev, MT_ARB_SCR,
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	udelay(1);

	mt76_wr(dev, MT_TIMEOUT_CCK, cck + reg_offset);
	mt76_wr(dev, MT_TIMEOUT_OFDM, ofdm + reg_offset);
	mt76_wr(dev, MT_IFS,
		FIELD_PREP(MT_IFS_EIFS, 360) |
		FIELD_PREP(MT_IFS_RIFS, 2) |
		FIELD_PREP(MT_IFS_SIFS, sifs) |
		FIELD_PREP(MT_IFS_SLOT, dev->slottime));

	if (dev->slottime < 20)
		val = MT7603_CFEND_RATE_DEFAULT;
	else
		val = MT7603_CFEND_RATE_11B;

	mt76_rmw_field(dev, MT_AGG_CONTROL, MT_AGG_CONTROL_CFEND_RATE, val);

	mt76_clear(dev, MT_ARB_SCR,
		   MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
}
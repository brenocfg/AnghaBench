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
typedef  scalar_t__ u32 ;
struct mt7615_dev {scalar_t__ last_cca_adj; scalar_t__ false_cca_cck; scalar_t__ false_cca_ofdm; int /*<<< orphan*/  scs_en; } ;

/* Variables and functions */
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int HZ ; 
 scalar_t__ MT_FRAC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MT_MIB_MB_SDR0 (int) ; 
 int /*<<< orphan*/  MT_MIB_RTS_COUNT_MASK ; 
 int /*<<< orphan*/  MT_MIB_RTS_RETRIES_COUNT_MASK ; 
 int /*<<< orphan*/  MT_WF_PHYCTRL_STAT_MDRDY_CCK ; 
 int /*<<< orphan*/  MT_WF_PHYCTRL_STAT_MDRDY_OFDM ; 
 int /*<<< orphan*/  MT_WF_PHYCTRL_STAT_PD_CCK ; 
 int /*<<< orphan*/  MT_WF_PHYCTRL_STAT_PD_OFDM ; 
 int /*<<< orphan*/  MT_WF_PHY_R0_B0_PHYCTRL_STS0 ; 
 int /*<<< orphan*/  MT_WF_PHY_R0_B0_PHYCTRL_STS5 ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt7615_mac_adjust_sensitivity (struct mt7615_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mt7615_mac_cca_stats_reset (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mac_set_default_sensitivity (struct mt7615_dev*) ; 
 scalar_t__ mt76_rr (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mt7615_mac_scs_check(struct mt7615_dev *dev)
{
	u32 val, rts_cnt = 0, rts_retries_cnt = 0, rts_err_rate = 0;
	u32 mdrdy_cck, mdrdy_ofdm, pd_cck, pd_ofdm;
	int i;

	if (!dev->scs_en)
		return;

	for (i = 0; i < 4; i++) {
		u32 data;

		val = mt76_rr(dev, MT_MIB_MB_SDR0(i));
		data = FIELD_GET(MT_MIB_RTS_RETRIES_COUNT_MASK, val);
		if (data > rts_retries_cnt) {
			rts_cnt = FIELD_GET(MT_MIB_RTS_COUNT_MASK, val);
			rts_retries_cnt = data;
		}
	}

	val = mt76_rr(dev, MT_WF_PHY_R0_B0_PHYCTRL_STS0);
	pd_cck = FIELD_GET(MT_WF_PHYCTRL_STAT_PD_CCK, val);
	pd_ofdm = FIELD_GET(MT_WF_PHYCTRL_STAT_PD_OFDM, val);

	val = mt76_rr(dev, MT_WF_PHY_R0_B0_PHYCTRL_STS5);
	mdrdy_cck = FIELD_GET(MT_WF_PHYCTRL_STAT_MDRDY_CCK, val);
	mdrdy_ofdm = FIELD_GET(MT_WF_PHYCTRL_STAT_MDRDY_OFDM, val);

	dev->false_cca_ofdm = pd_ofdm - mdrdy_ofdm;
	dev->false_cca_cck = pd_cck - mdrdy_cck;
	mt7615_mac_cca_stats_reset(dev);

	if (rts_cnt + rts_retries_cnt)
		rts_err_rate = MT_FRAC(rts_retries_cnt,
				       rts_cnt + rts_retries_cnt);

	/* cck */
	mt7615_mac_adjust_sensitivity(dev, rts_err_rate, false);
	/* ofdm */
	mt7615_mac_adjust_sensitivity(dev, rts_err_rate, true);

	if (time_after(jiffies, dev->last_cca_adj + 10 * HZ))
		mt7615_mac_set_default_sensitivity(dev);
}
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
typedef  int u16 ;
struct mt7615_dev {int false_cca_ofdm; int false_cca_cck; int ofdm_sensitivity; int cck_sensitivity; int /*<<< orphan*/  last_cca_adj; int /*<<< orphan*/  mt76; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ MT_FRAC (int,int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_MIN_PRI_PWR ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_CCK (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_CCK_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_OFDM (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_OFDM_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_RXTD_CCK_PD ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_CCK (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_CCK_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_RXTD_CCK_PD ; 
 int /*<<< orphan*/  jiffies ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mt7615_mac_set_default_sensitivity (struct mt7615_dev*) ; 
 int mt76_get_min_avg_rssi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7615_mac_adjust_sensitivity(struct mt7615_dev *dev,
			      u32 rts_err_rate, bool ofdm)
{
	int false_cca = ofdm ? dev->false_cca_ofdm : dev->false_cca_cck;
	u16 def_th = ofdm ? -98 : -110;
	bool update = false;
	s8 *sensitivity;
	int signal;

	sensitivity = ofdm ? &dev->ofdm_sensitivity : &dev->cck_sensitivity;
	signal = mt76_get_min_avg_rssi(&dev->mt76);
	if (!signal) {
		mt7615_mac_set_default_sensitivity(dev);
		return;
	}

	signal = min(signal, -72);
	if (false_cca > 500) {
		if (rts_err_rate > MT_FRAC(40, 100))
			return;

		/* decrease coverage */
		if (*sensitivity == def_th && signal > -90) {
			*sensitivity = -90;
			update = true;
		} else if (*sensitivity + 2 < signal) {
			*sensitivity += 2;
			update = true;
		}
	} else if ((false_cca > 0 && false_cca < 50) ||
		   rts_err_rate > MT_FRAC(60, 100)) {
		/* increase coverage */
		if (*sensitivity - 2 >= def_th) {
			*sensitivity -= 2;
			update = true;
		}
	}

	if (*sensitivity > signal) {
		*sensitivity = signal;
		update = true;
	}

	if (update) {
		u16 val;

		if (ofdm) {
			/* DBDC not supported */
			val = *sensitivity * 2 + 512;
			mt76_rmw(dev, MT_WF_PHY_B0_MIN_PRI_PWR,
				 MT_WF_PHY_B0_PD_OFDM_MASK,
				 MT_WF_PHY_B0_PD_OFDM(val));
		} else {
			val = *sensitivity + 256;
			mt76_rmw(dev, MT_WF_PHY_B0_RXTD_CCK_PD,
				 MT_WF_PHY_B0_PD_CCK_MASK,
				 MT_WF_PHY_B0_PD_CCK(val));
			mt76_rmw(dev, MT_WF_PHY_B1_RXTD_CCK_PD,
				 MT_WF_PHY_B1_PD_CCK_MASK,
				 MT_WF_PHY_B1_PD_CCK(val));
		}
		dev->last_cca_adj = jiffies;
	}
}
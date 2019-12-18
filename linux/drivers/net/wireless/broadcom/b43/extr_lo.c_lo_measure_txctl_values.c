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
struct b43_phy {int rev; int radio_ver; int radio_rev; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_txpower_lo_control {int tx_bias; int tx_magn; int /*<<< orphan*/  txctl_measured_time; } ;
struct b43_phy_g {int max_lb_gain; struct b43_txpower_lo_control* lo_control; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  b43_gphy_set_baseband_attenuation (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  has_loopback_gain (struct b43_phy*) ; 
 scalar_t__ has_tx_magnification (struct b43_phy*) ; 
 int /*<<< orphan*/  jiffies ; 
 int lo_measure_feedthrough (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int lo_txctl_register_table (struct b43_wldev*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lo_measure_txctl_values(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_txpower_lo_control *lo = gphy->lo_control;
	u16 reg, mask;
	u16 trsw_rx, pga;
	u16 radio_pctl_reg;

	static const u8 tx_bias_values[] = {
		0x09, 0x08, 0x0A, 0x01, 0x00,
		0x02, 0x05, 0x04, 0x06,
	};
	static const u8 tx_magn_values[] = {
		0x70, 0x40,
	};

	if (!has_loopback_gain(phy)) {
		radio_pctl_reg = 6;
		trsw_rx = 2;
		pga = 0;
	} else {
		int lb_gain;	/* Loopback gain (in dB) */

		trsw_rx = 0;
		lb_gain = gphy->max_lb_gain / 2;
		if (lb_gain > 10) {
			radio_pctl_reg = 0;
			pga = abs(10 - lb_gain) / 6;
			pga = clamp_val(pga, 0, 15);
		} else {
			int cmp_val;
			int tmp;

			pga = 0;
			cmp_val = 0x24;
			if ((phy->rev >= 2) &&
			    (phy->radio_ver == 0x2050) && (phy->radio_rev == 8))
				cmp_val = 0x3C;
			tmp = lb_gain;
			if ((10 - lb_gain) < cmp_val)
				tmp = (10 - lb_gain);
			if (tmp < 0)
				tmp += 6;
			else
				tmp += 3;
			cmp_val /= 4;
			tmp /= 4;
			if (tmp >= cmp_val)
				radio_pctl_reg = cmp_val;
			else
				radio_pctl_reg = tmp;
		}
	}
	b43_radio_maskset(dev, 0x43, 0xFFF0, radio_pctl_reg);
	b43_gphy_set_baseband_attenuation(dev, 2);

	reg = lo_txctl_register_table(dev, &mask, NULL);
	mask = ~mask;
	b43_radio_mask(dev, reg, mask);

	if (has_tx_magnification(phy)) {
		int i, j;
		int feedthrough;
		int min_feedth = 0xFFFF;
		u8 tx_magn, tx_bias;

		for (i = 0; i < ARRAY_SIZE(tx_magn_values); i++) {
			tx_magn = tx_magn_values[i];
			b43_radio_maskset(dev, 0x52, 0xFF0F, tx_magn);
			for (j = 0; j < ARRAY_SIZE(tx_bias_values); j++) {
				tx_bias = tx_bias_values[j];
				b43_radio_maskset(dev, 0x52, 0xFFF0, tx_bias);
				feedthrough =
				    lo_measure_feedthrough(dev, 0, pga,
							   trsw_rx);
				if (feedthrough < min_feedth) {
					lo->tx_bias = tx_bias;
					lo->tx_magn = tx_magn;
					min_feedth = feedthrough;
				}
				if (lo->tx_bias == 0)
					break;
			}
			b43_radio_write16(dev, 0x52,
					  (b43_radio_read16(dev, 0x52)
					   & 0xFF00) | lo->tx_bias | lo->
					  tx_magn);
		}
	} else {
		lo->tx_magn = 0;
		lo->tx_bias = 0;
		b43_radio_mask(dev, 0x52, 0xFFF0);	/* TX bias == 0 */
	}
	lo->txctl_measured_time = jiffies;
}
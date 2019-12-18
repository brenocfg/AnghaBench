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
typedef  int u16 ;
struct b43_phy {struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int trsw_rx_gain; int lna_lod_gain; int pga_gain; int lna_gain; } ;
typedef  int s16 ;

/* Variables and functions */
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_loopback_gain (struct b43_phy*) ; 

__attribute__((used)) static void lo_measure_gain_values(struct b43_wldev *dev,
				   s16 max_rx_gain, int use_trsw_rx)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (max_rx_gain < 0)
		max_rx_gain = 0;

	if (has_loopback_gain(phy)) {
		int trsw_rx_gain;

		if (use_trsw_rx) {
			trsw_rx_gain = gphy->trsw_rx_gain / 2;
			if (max_rx_gain >= trsw_rx_gain) {
				trsw_rx_gain = max_rx_gain - trsw_rx_gain;
			}
		} else
			trsw_rx_gain = max_rx_gain;
		if (trsw_rx_gain < 9) {
			gphy->lna_lod_gain = 0;
		} else {
			gphy->lna_lod_gain = 1;
			trsw_rx_gain -= 8;
		}
		trsw_rx_gain = clamp_val(trsw_rx_gain, 0, 0x2D);
		gphy->pga_gain = trsw_rx_gain / 3;
		if (gphy->pga_gain >= 5) {
			gphy->pga_gain -= 5;
			gphy->lna_gain = 2;
		} else
			gphy->lna_gain = 0;
	} else {
		gphy->lna_gain = 0;
		gphy->trsw_rx_gain = 0x20;
		if (max_rx_gain >= 0x14) {
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 2;
		} else if (max_rx_gain >= 0x12) {
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 1;
		} else if (max_rx_gain >= 0xF) {
			gphy->lna_lod_gain = 1;
			gphy->pga_gain = 0;
		} else {
			gphy->lna_lod_gain = 0;
			gphy->pga_gain = 0;
		}
	}

	tmp = b43_radio_read16(dev, 0x7A);
	if (gphy->lna_lod_gain == 0)
		tmp &= ~0x0008;
	else
		tmp |= 0x0008;
	b43_radio_write16(dev, 0x7A, tmp);
}
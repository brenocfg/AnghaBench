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
typedef  int u32 ;
struct mt7601u_dev {int* rf_pa_mode; } ;
typedef  int s16 ;

/* Variables and functions */
#define  MT_PHY_TYPE_CCK 129 
#define  MT_PHY_TYPE_OFDM 128 

__attribute__((used)) static s16
mt7601u_phy_rf_pa_mode_val(struct mt7601u_dev *dev, int phy_mode, int tx_rate)
{
	static const s16 decode_tb[] = { 0, 8847, -5734, -5734 };
	u32 reg;

	switch (phy_mode) {
	case MT_PHY_TYPE_OFDM:
		tx_rate += 4;
		/* fall through */
	case MT_PHY_TYPE_CCK:
		reg = dev->rf_pa_mode[0];
		break;
	default:
		reg = dev->rf_pa_mode[1];
		break;
	}

	return decode_tb[(reg >> (tx_rate * 2)) & 0x3];
}
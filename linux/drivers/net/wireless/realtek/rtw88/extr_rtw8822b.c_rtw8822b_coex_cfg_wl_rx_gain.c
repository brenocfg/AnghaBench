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
typedef  size_t u8 ;
typedef  int u32 ;
struct rtw_coex_dm {int cur_wl_rx_low_gain_en; } ;
struct rtw_coex {struct rtw_coex_dm dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int REG_RX_GAIN_EN ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  RF_RCK ; 
 int /*<<< orphan*/  RF_RCKD ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int const) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtw8822b_coex_cfg_wl_rx_gain(struct rtw_dev *rtwdev, bool low_gain)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	/* WL Rx Low gain on */
	static const u32 wl_rx_low_gain_on[] = {
		0xff000003, 0xbd120003, 0xbe100003, 0xbf080003, 0xbf060003,
		0xbf050003, 0xbc140003, 0xbb160003, 0xba180003, 0xb91a0003,
		0xb81c0003, 0xb71e0003, 0xb4200003, 0xb5220003, 0xb4240003,
		0xb3260003, 0xb2280003, 0xb12a0003, 0xb02c0003, 0xaf2e0003,
		0xae300003, 0xad320003, 0xac340003, 0xab360003, 0x8d380003,
		0x8c3a0003, 0x8b3c0003, 0x8a3e0003, 0x6e400003, 0x6d420003,
		0x6c440003, 0x6b460003, 0x6a480003, 0x694a0003, 0x684c0003,
		0x674e0003, 0x66500003, 0x65520003, 0x64540003, 0x64560003,
		0x007e0403
	};

	/* WL Rx Low gain off */
	static const u32 wl_rx_low_gain_off[] = {
		0xff000003, 0xf4120003, 0xf5100003, 0xf60e0003, 0xf70c0003,
		0xf80a0003, 0xf3140003, 0xf2160003, 0xf1180003, 0xf01a0003,
		0xef1c0003, 0xee1e0003, 0xed200003, 0xec220003, 0xeb240003,
		0xea260003, 0xe9280003, 0xe82a0003, 0xe72c0003, 0xe62e0003,
		0xe5300003, 0xc8320003, 0xc7340003, 0xc6360003, 0xc5380003,
		0xc43a0003, 0xc33c0003, 0xc23e0003, 0xc1400003, 0xc0420003,
		0xa5440003, 0xa4460003, 0xa3480003, 0xa24a0003, 0xa14c0003,
		0x834e0003, 0x82500003, 0x81520003, 0x80540003, 0x65560003,
		0x007e0403
	};
	u8 i;

	if (low_gain == coex_dm->cur_wl_rx_low_gain_en)
		return;

	coex_dm->cur_wl_rx_low_gain_en = low_gain;

	if (coex_dm->cur_wl_rx_low_gain_en) {
		for (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_on); i++)
			rtw_write32(rtwdev, REG_RX_GAIN_EN, wl_rx_low_gain_on[i]);

		/* set Rx filter corner RCK offset */
		rtw_write_rf(rtwdev, RF_PATH_A, RF_RCKD, 0x2, 0x1);
		rtw_write_rf(rtwdev, RF_PATH_A, RF_RCK, 0x3f, 0x3f);
		rtw_write_rf(rtwdev, RF_PATH_B, RF_RCKD, 0x2, 0x1);
		rtw_write_rf(rtwdev, RF_PATH_B, RF_RCK, 0x3f, 0x3f);
	} else {
		for (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_off); i++)
			rtw_write32(rtwdev, 0x81c, wl_rx_low_gain_off[i]);

		/* set Rx filter corner RCK offset */
		rtw_write_rf(rtwdev, RF_PATH_A, RF_RCK, 0x3f, 0x4);
		rtw_write_rf(rtwdev, RF_PATH_A, RF_RCKD, 0x2, 0x0);
		rtw_write_rf(rtwdev, RF_PATH_B, RF_RCK, 0x3f, 0x4);
		rtw_write_rf(rtwdev, RF_PATH_B, RF_RCKD, 0x2, 0x0);
	}
}